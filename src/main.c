
#include "minishell.h"

void	get_pid(t_ms *ms, char **envp)
{
	pid_t	pid;
	int		fd;
	const char *cmd3[] = {"/usr/bin/pgrep", "minishell", 0};

	fd = open(PID_BUFFER, O_CREAT | O_TRUNC | O_RDWR, 0777);
	pid = fork();
	if (!pid)
	{
		dup2(fd, STDOUT_FILENO);
		execve(cmd3[0], (char **)cmd3, envp);
	}
	else
	{
		close(fd);
		fd = open(PID_BUFFER, O_RDWR);
		waitpid(pid, 0, 0);
		ms->pid = get_next_line(fd);
		*ft_strrchr(ms->pid, '\n') = 0;
		close(fd);
		unlink(PID_BUFFER);
	}
}

void	free_parser_token(t_ms *ms)
{
	t_lexer_token	*ltmp;
	t_parser_token	*ptmp;

	while(ms->parser_token)
	{
		ptmp = ms->parser_token->next;
		while (ms->parser_token->lxr_list)
		{
			ltmp = ms->parser_token->lxr_list->next;
			free (ms->parser_token->lxr_list);
			ms->parser_token->lxr_list =  ltmp;
		}
		free (ms->parser_token);
		ms->parser_token = ptmp;
	}
}

int	main(int argc, char ** argv, char **envp)
{
	t_ms	ms;

	(void) argv;
	ft_memset(&ms, 0, sizeof(t_ms));
	if (argc != 1)
		return (ft_putendl_fd("Invalid arguments.", 2), -1);
	if (!exist_envp(envp))
		return (ft_putendl_fd("Env doesn't exist.", 2), -1);
	ms.envp = envp;
	fill_envp(&ms, envp);
	set_default_paths(&ms);
	get_pid(&ms, envp);
	dollardollar(&ms, envp);
	while (1)
	{
		if(ms.parser_token)
			free_parser_token(&ms);
		set_prompt(&ms);
		if (ms.rline && *(ms.rline))
			add_history(ms.rline);
		if (!ft_strncmp(ms.rline, "exit", 5))
			return (printf("exit\n"), free_exit(&ms), 0);
		if (!ft_strncmp(ms.rline, "clear", 6))
			system("clear");
		if (!ft_strncmp(ms.rline, "env", 4))
			ft_env(&ms);
		else
		{
				if (!create_shadow(&ms))
					return (free_exit(&ms), 0);
				expand_test(&ms);
				tokenize_rline(&ms);
				if (ms.lexer_token && !ft_strncmp(ms.lexer_token->arg, "cd", 3))
					ft_cd(&ms);
				if (ms.lexer_token && !ft_strncmp(ms.lexer_token->arg, "unset", 6))
					ft_unset(&ms, ms.lexer_token->next->arg);
				if (!ft_strncmp(ms.lexer_token->arg, "export", 7))
					ft_export(&ms, ms.lexer_token->next->arg);
				tokenize_parser(&ms);
		}
	}
	//system("leaks minishell");
	return (1);
}
