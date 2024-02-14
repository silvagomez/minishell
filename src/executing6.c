
#include "minishell.h"

void	organize_fd_simple_father(t_ms *ms, t_parser_token *ptoken)
{
	if (parser_token_count(ms->parser_token) > 1)
	{
		dup2(ms->tube[ptoken->token_id - 1], STDIN_FILENO);
		close(ms->tube[ptoken->token_id - 1]);
	}
	if (ptoken->is_input)
		close (ptoken->input_fd);
	if (ptoken->is_output)
		close (ptoken->output_fd);
	if (ptoken->is_here_doc)
		close (ptoken->hd_pipe[0]);
}

void	simple_child(t_ms *ms, t_parser_token *ptoken)
{
	if (!ms->pathlist)
		error_handling_exit(ERR_PATH, 127);
	if (get_command(ms, ptoken))
	{
		check_ptoken_heredoc(ptoken);
		check_ptoken_input_heredoc(ptoken);
		check_ptoken_output_fd(ptoken);
		if (execve(ms->cmd_array[0], ms->cmd_array, ms->envp) == -1)
			error_handling(ERR_EXEC, EXIT_FAILURE);
		error_handling_free_prompt(ms, ERR_CNOF, 127);
	}
	else
		error_handling_free_prompt(ms, ERR_CNOF, 127);
}

/*
 * This functions executes a binary program  on the way of simple command, 
 * that means ptoken_count == 1
 */
void	execute_simple(t_ms *ms, t_parser_token *ptoken)
{
	int		pid;
	int		status;

	pid = fork();
	if (!pid)
		simple_child(ms, ptoken);
	else
	{
		if (parser_token_count(ms->parser_token) > 1)
			close (ms->tube[ptoken->token_id]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
		{
			printf("Child exited with status %d\n", WEXITSTATUS(status));
			g_status = WEXITSTATUS(status);
		}
		else if (WIFSIGNALED(status) && ptoken->is_here_doc)
		{
			printf("Child terminated by signal %d\n", WTERMSIG(status));
			g_status = 1;
		}
		else if (WIFSIGNALED(status))
		{
			printf("Child terminated by signal %d\n", WTERMSIG(status));
			g_status = 128 + WTERMSIG(status);
		}
		else
			g_status = status;
		organize_fd_simple_father(ms, ptoken);
	}
}
