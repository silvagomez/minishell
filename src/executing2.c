
#include "minishell.h"

void	wait_children(t_ms *ms, int status)
{
	t_pid_token	*pid_token;

	pid_token = ms->pid_token;
	while (pid_token)
	{
		waitpid(pid_token->child_pid, NULL, 0);
		pid_token = pid_token->next;
	}
	if (WIFEXITED(status))
	{
		printf("Child exited with status %d\n", WEXITSTATUS(status));
		g_status = WEXITSTATUS(status);
	}
	else if (WIFSIGNALED(status))
	{
		printf("Child terminated by signal %d\n", WTERMSIG(status));
		g_status = 128 + WTERMSIG(status);
	}
	else
		g_status = status;
}

void	child_last_child(t_ms *ms, t_parser_token *ptoken)
{
	if (!ms->pathlist)
		error_handling_exit(ERR_PATH, 127);
	check_command(ms, ptoken);
	check_ptoken_heredoc(ptoken);
	check_ptoken_input_heredoc(ptoken);
	check_ptoken_output_fd(ptoken);
	check_if_builtin(ms, ptoken);
	if (execve(ms->cmd_array[0], ms->cmd_array, ms->envp) == -1)
		error_handling(ERR_EXEC, EXIT_FAILURE);
}

void	execute_last_child(t_ms *ms, t_parser_token *ptoken)
{
	int	status;

	ptoken->pid = fork();
	if (ptoken->pid < 0)
		error_handling(ERR_FKFL, EXIT_FAILURE);
	pid_token_add(&ms->pid_token, pid_token_new(ms, ptoken->pid));
	if (!ptoken->pid)
		child_last_child(ms, ptoken);
	else
	{
		waitpid(ptoken->pid, &status, 0);
		if (ptoken_count(ms->parser_token) > 1)
			close (ms->tube[ptoken->token_id - 2]);
		if (ptoken_count(ms->parser_token) > 1)
		{
			dup2(ms->tube[ptoken->token_id - 3], STDIN_FILENO);
			close(ms->tube[ptoken->token_id - 3]);
		}
		if (ptoken->is_output)
			close (ptoken->output_fd);
		if (ptoken->is_input)
			close (ptoken->input_fd);
		wait_children(ms, status);
	}
}

/*
 * Execution way of pipeline
 */
void	token_last_child(t_ms *ms, t_parser_token *ptoken)
{
	free(ms->cmd_array);
	ms->cmd_array = NULL;
	if (ptoken->tag == 0)
		create_array(ms, ptoken->lxr_list);
	execute_last_child(ms, ptoken);
}
