
#include "minishell.h"

void	get_pid(t_ms *ms, char **envp)
{
	pid_t	pid;
	int		fd;
	char	**cmd;
	char	*tmp;
	int		rd;

	tmp = malloc (100);
	cmd = malloc(sizeof(char *) * 3);
	fd = open("temp", O_CREAT | O_RDWR, 0777);
	pid = fork();
	if (!pid)
	{
		cmd[0] = "/usr/bin/pgrep";
		cmd[1] = "minishell";
		cmd[2] = 0;
		dup2(fd, STDOUT_FILENO);
		execve("/usr/bin/pgrep", cmd, envp);
	}
	else
	{
		wait(NULL);
		free(cmd);
		rd = read(fd, tmp, 100);
		tmp[rd] = 0;
		ms->pid = tmp;
		//printf("DENTRO: %s", tmp);
		close(fd);
		unlink("temp");
	}
}

int	main(int argc, char ** argv, char **envp)
{
	t_ms	ms;

/* 	if (!path_exists)
		return (OUT); */
	(void) argv;
	ms.envlst = NULL;
	if (argc != 1)
		return (ft_putendl_fd("Invalid arguments.", 2), -1);
	if (!exist_envp(envp))
		return (ft_putendl_fd("Env doesn't exist.", 2), -1);
	fill_envp(&ms, envp);
	set_default_paths(&ms);
	//get_pid(&ms, envp);
	//printf("TEST: %s\n", getenv("var1"));
	while (1)
	{
		//printf("PID: %s",ms.pid);
		set_prompt(&ms);
		if (ms.rline && *(ms.rline))
			add_history(ms.rline);
		if (!ft_strncmp(ms.rline, "exit", 5))
		{
			ft_printf("exit\n");
			break ;
		}
		if (!ft_strncmp(ms.rline, "clear", 6))
			system("clear");
		if (!ft_strncmp(ms.rline, "env", 4))
			ft_env(&ms);
		else
		{
			/* if (!is_valid_quoting(&ms))
				ft_printf("COMILLAS ERRÓNEAS\n");
			else
			{ */
				//printf("rline introducido: %s", ms.rline);
				//count_pipes(&ms);
				//printf("QUOTE: %c\n%s%s\n", ms.quote, ms.rline, ms.shadow);
				//ms.rline[ft_strlen(ms.rline) - 1] = 0;
				if (!create_shadow(&ms))
					return (free_exit(&ms), 0);
				expand_test(&ms);
				tokenize_rline(&ms);
				if (ms.lexer_token && !ft_strncmp(ms.lexer_token->arg, "cd", 3))
					ft_cd(&ms);
				//if (!ft_strncmp(&ms))
				//	ft_cd(
			/* } */
		}
	}
	//system("leaks minishell");
	return (1);
}
