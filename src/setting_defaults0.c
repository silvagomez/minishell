
#include "minishell.h"

void	os_child(int fd, const char **cmd, char **envp)
{
	dup2(fd, STDOUT_FILENO);
	if (execve(cmd[0], (char **)cmd, envp) == -1)
		error_handling(ERR_EXEC, EXIT_FAILURE);
	exit(EXIT_SUCCESS);
}

void	get_os(t_ms *ms, int fd)
{
	char		*line;
	
	line = get_next_line(fd);
	ms->os_name = ft_strdup(line);
	*ft_strrchr(ms->os_name, '\n') = 0;
	free(line);
}

/*
 * This behind scene will launch a execve to get the uname
 */
void	set_os(t_ms *ms, char **envp)
{
	int			fd;
	pid_t		pid;
	const char	*cmd[] = {"/usr/bin/uname", 0, 0};
	int			status;

	fd = open(OS_NAME, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd < 0)
		error_handling(ERR_ONFD, EXIT_FAILURE);
	pid = fork();
	if (!pid)
		os_child(fd, cmd, envp);
	else
	{
		close(fd);
		waitpid(pid, &status, 0);
		fd = open(OS_NAME, O_RDWR);
		get_os(ms, fd);
		close(fd);
		unlink(OS_NAME);
		g_status = status;
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
		ft_export(ms, "SHLV=1", 0);
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
