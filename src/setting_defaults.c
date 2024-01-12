
#include "minishell.h"

void	os_child(int fd, const char **cmd, char **envp)
{
	dup2(fd, STDOUT_FILENO);
	if (execve(cmd[0], (char **)cmd, envp) == -1)
		printf("*+EXECVE FAILED+*\n");
	exit(0);
}

/*
 * This behind scene will launch a execve to get the uname
 */
void	set_os(t_ms *ms, char **envp)
{
	int			fd;
	pid_t		pid;
	const char	*cmd[] = {"/usr/bin/uname", 0, 0};
	char		*line;

	fd = open(OS_NAME, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd < 0)
		ft_putendl_fd("Error creating script file", 2);
	pid = fork();
	if (!pid)
		os_child(fd, cmd, envp);
	else
	{
		close(fd);
		waitpid(pid, 0, 0);
		fd = open(OS_NAME, O_RDWR);
		line = get_next_line(fd);
		ms->os_name = ft_strdup(line);
		*ft_strrchr(ms->os_name, '\n') = 0;
		free(line);
		close(fd);
		unlink(OS_NAME);
	}
}

/*
 * This function +1 to the env variable SHLVL.
 */
void	plus_one_shlvl(t_ms *ms)
{
	t_envlst	*node;
	char		*content;
	int			level;

	node = find_env(ms, "SHLVL");
	if (!node)
	{
		ft_export(ms, "SHLV=1", 0);
		//envlst_add(&ms->envlst, envlst_new(ms, "SHLVL=1"));
		//node = find_env(ms, "SHLVL");
	}
	level = ft_atoi(node->content);
	level++;
	content = ft_itoa(level);
	update_env_content(ms, "SHLVL", content);
	free(content);
}

/*
 * This function fills data to *ms varaibles and set a deault env variables 
 * when a shell is launching in this case *envlist.
 */
void	set_default_paths(t_ms *ms, char **envp)
{
	ms->user = ft_strdup(ft_getenv(ms, "USER"));
	ms->home = ft_strdup(ft_getenv(ms, "HOME"));
	ms->pwd = ft_strdup(ft_getenv(ms, "PWD"));
	ms->pwd_ppt = ft_strdup(ft_getenv(ms, "PWD"));
	update_env_content(ms, "_", "/usr/bin/env");
	plus_one_shlvl(ms);
	ft_unset(ms, "OLDPWD");
	set_os(ms, envp);
	ms->dflt_input = dup(STDIN_FILENO);
	ms->dflt_output = dup(STDOUT_FILENO);
}
