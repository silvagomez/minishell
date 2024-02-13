
#include "minishell.h"

/*
 * This functions allocates memory to a **array in the case of a bin-command
 */
void	create_array(t_ms *ms, t_lexer_token *ltoken)
{
	t_lexer_token	*ltmp;
	int				i;

	ms->cmd_array = malloc(sizeof(char *) * (lexer_token_count(ltoken) + 1));
	ltmp = ltoken;
	i = 0;
	while (ltmp)
	{
		ms->cmd_array[i] = ltmp->arg;
		i++;
		ltmp = ltmp->next;
	}
	ms->cmd_array[i] = NULL;
}

/*
 * This function seeks in pathlist if the arg is a binary program (command)
 */
int	get_command(t_ms *ms, t_parser_token *ptoken)
{
	int	i;

	i = -1;
	while (ms->pathlist[++i])
	{
		free (ms->cmd);
		ms->cmd = ft_strjoin(ms->pathlist[i], ptoken->lxr_list->arg);
		if (access(ms->cmd, F_OK) == 0)
		{
			free(ms->cmd_array[0]);
			ms->cmd_array[0] = ft_strdup(ms->cmd);
			break ;
		}
	}
	if (ms->pathlist[i] == NULL)
	{
		if (access(ptoken->lxr_list->arg, F_OK) == 0)
		{
			free (ms->cmd); //TESTEAR CON RUTA ABSOLUTA DE PROGRAMAS!!
			ms->cmd = ptoken->lxr_list->arg;
		}
		else
			return (0);
	}
	return (1);
}

void	organize_fd_ptoken(t_ms *ms, t_parser_token *ptoken)
{
	if (parser_token_count(ms->parser_token) > 1)
		close (ms->tube[ptoken->token_id]);
	if (parser_token_count(ms->parser_token) > 1)
	{
		dup2(ms->tube[ptoken->token_id - 1], STDIN_FILENO);
		close(ms->tube[ptoken->token_id - 1]);
	}
	if (ptoken->is_input)
		close (ptoken->input_fd);
}

/*
void	organize_fd_ptoken_await(t_ms *ms, t_parser_token *ptoken)
{
}
*/

/*
 * This function checks is ptoken->arg is a binary program (command)
 */
void	check_command(t_ms *ms, t_parser_token *ptoken)
{
	if (ptoken->tag == 0)
	{
		if (!get_command(ms, ptoken))
			error_handling_exit(ERR_CNOF, 127);
	}
}

void	check_ptoken_heredoc(t_parser_token *ptoken)
{
	if (ptoken->is_here_doc)
	{
		ptoken->input_fd = dup(ptoken->hd_pipe[0]);
		close (ptoken->hd_pipe[0]);
	}
}

void	check_ptoken_input_heredoc(t_parser_token *ptoken)
{
	if (ptoken->is_input || ptoken->is_here_doc)
	{
		dup2(ptoken->input_fd, STDIN_FILENO);
		close (ptoken->input_fd);
	}
}

void	check_ptoken_output_fd(t_parser_token *ptoken)
{
	if (ptoken->output_fd > 2)
	{
		dup2(ptoken->output_fd, STDOUT_FILENO);
		close (ptoken->output_fd);
	}
}

void	check_if_builtin_program(t_ms *ms, t_parser_token *ptoken)
{
	int status;

	if (ptoken->tag > 0)
	{
		//if (is_builtin_allowed_pipelines(ptoken->lxr_list))
			status = execute_builtin_pipelines(ms, ptoken->lxr_list);
		free_per_prompt(ms);
		exit(status);
	}
}

//////// INI------------------------------------------------------------------/
/*
 * OLD FUNCTION FOR STRUCTURE IDEAS AND TESTS
 */
void	execute_program(t_ms *ms, t_parser_token *ptoken)
{
	//int	status;

	ptoken->pid = fork();
	if (ptoken->pid < 0)
		error_handling(ERR_CNOF, EXIT_FAILURE);
	pid_token_add(&ms->pid_token, pid_token_new(ms, ptoken->pid));
	if (!ptoken->pid)
	{
		check_command(ms, ptoken);
		check_ptoken_heredoc(ptoken);
		check_ptoken_input_heredoc(ptoken);
		check_ptoken_output_fd(ptoken);
		check_if_builtin_program(ms, ptoken);
		if (execve(ms->cmd_array[0], ms->cmd_array, ms->envp) == -1)
			error_handling(ERR_EXEC, EXIT_FAILURE);
		free_per_prompt(ms);
	}
	else
	{
		if (parser_token_count(ms->parser_token) > 1)
			close (ms->tube[ptoken->token_id]);
		waitpid(ptoken->pid, NULL, 0);
		if (parser_token_count(ms->parser_token) > 1)
		{
			dup2(ms->tube[ptoken->token_id - 1], STDIN_FILENO);
			close(ms->tube[ptoken->token_id - 1]);
		}
		if (ptoken->is_input)
			close (ptoken->input_fd);
	}
}
//---------------------------------------------------------------END //////////

/*
 * This functions executes our builtins on the way of simple command, 
 * that means ptoken_count == 1
 */
int	execute_builtin(t_ms *ms, t_parser_token *ptoken, t_lexer_token *ltoken)
{
	int	status;

	(void)ms;
	(void)ptoken;
	status = 1;
	if (!ft_strncmp(ltoken->arg, "echo", ft_strlen(ltoken->arg) + 1))
		status = ft_echo(ltoken->next);
	else if (!ft_strncmp(ltoken->arg, "cd", ft_strlen(ltoken->arg) + 1))
		status = ft_cd(ms, ltoken);
	else if (!ft_strncmp(ltoken->arg, "pwd", ft_strlen(ltoken->arg) + 1))
		status = ft_pwd(ms, ltoken);
	else if (!ft_strncmp(ltoken->arg, "export", ft_strlen(ltoken->arg) + 1))
		status = execute_export(ms, ltoken);
	else if (!ft_strncmp(ltoken->arg, "unset", ft_strlen(ltoken->arg) + 1))
		status = execute_unset(ms, ltoken);
	else if (!ft_strncmp(ltoken->arg, "env", ft_strlen(ltoken->arg) + 1))
		status = ft_env(ms, ltoken);
	else if (!ft_strncmp(ltoken->arg, "declare", ft_strlen(ltoken->arg) + 1))
		status = ft_declare(ms, ltoken);
	else if (!ft_strncmp(ltoken->arg, "exit", ft_strlen(ltoken->arg) + 1))
		ft_exit(ms, ltoken->next);
	organize_fd_ptoken(ms, ptoken);
	g_status = status;
	return (status);
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

void	organize_fd_simple_father(t_ms *ms, t_parser_token *ptoken)
{
	if (parser_token_count(ms->parser_token) > 1)
	{
		dup2(ms->tube[ptoken->token_id - 1], STDIN_FILENO);
		close(ms->tube[ptoken->token_id - 1]);
	}
	if (ptoken->is_input)
		close (ptoken->input_fd);
	if (ptoken->is_here_doc)
		close (ptoken->hd_pipe[0]);
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

/*
 * This function verifies which builitins are allowed to write on pipes,
 * on the way ptoken > 1
 */
int	is_builtin_allowed_pipelines(t_lexer_token *ltoken)
{
	if (!ft_strncmp(ltoken->arg, "echo", ft_strlen(ltoken->arg) + 1))
		return (1);
	else if (!ft_strncmp(ltoken->arg, "pwd", ft_strlen(ltoken->arg) + 1))
		return (1);
	else if (!ft_strncmp(ltoken->arg, "env", ft_strlen(ltoken->arg) + 1))
		return (1);
	else if (!ft_strncmp(ltoken->arg, "export", ft_strlen(ltoken->arg) + 1))
	{
		if (ltoken->next == NULL)
			return (1);
	}
	return (0);
}

/*
 * This function execute builitins are allowed to write on pipes,
 * on the way ptoken > 1
 */
int	execute_builtin_pipelines(t_ms *ms, t_lexer_token *ltoken)
{
	int	status;

	status = 0;
	/*
	if (!ft_strncmp(ltoken->arg, "echo", ft_strlen(ltoken->arg) + 1))
		status = ft_echo(ltoken->next);
	else if (!ft_strncmp(ltoken->arg, "pwd", ft_strlen(ltoken->arg) + 1))
		status = ft_pwd(ms, ltoken);
	else if (!ft_strncmp(ltoken->arg, "env", ft_strlen(ltoken->arg) + 1))
		status = ft_env(ms, ltoken);
	else if (!ft_strncmp(ltoken->arg, "export", ft_strlen(ltoken->arg) + 1))
		status = execute_export(ms, ltoken);
	else if (!ft_strncmp(ltoken->arg, "declare", ft_strlen(ltoken->arg) + 1))
		status = ft_declare(ms, ltoken);
*/
	if (!ft_strncmp(ltoken->arg, "echo", ft_strlen(ltoken->arg) + 1))
		status = ft_echo(ltoken->next);
	else if (!ft_strncmp(ltoken->arg, "cd", ft_strlen(ltoken->arg) + 1))
		status = ft_cd(ms, ltoken);
	else if (!ft_strncmp(ltoken->arg, "pwd", ft_strlen(ltoken->arg) + 1))
		status = ft_pwd(ms, ltoken);
	else if (!ft_strncmp(ltoken->arg, "export", ft_strlen(ltoken->arg) + 1))
		status = execute_export(ms, ltoken);
	else if (!ft_strncmp(ltoken->arg, "unset", ft_strlen(ltoken->arg) + 1))
		status = execute_unset(ms, ltoken);
	else if (!ft_strncmp(ltoken->arg, "env", ft_strlen(ltoken->arg) + 1))
		status = ft_env(ms, ltoken);
	else if (!ft_strncmp(ltoken->arg, "declare", ft_strlen(ltoken->arg) + 1))
		status = ft_declare(ms, ltoken);
	else if (!ft_strncmp(ltoken->arg, "exit", ft_strlen(ltoken->arg) + 1))
		ft_exit(ms, ltoken->next);
	return (status);
}

void	check_if_builtin(t_ms *ms, t_parser_token *ptoken)
{
	int status;

	if (ptoken->tag > 0)
	{
		//if (is_builtin_allowed_pipelines(ptoken->lxr_list))
			status = execute_builtin_pipelines(ms, ptoken->lxr_list);
		exit(status);
	}
}

void	execute_child(t_ms *ms, t_parser_token *ptoken)
{
	ptoken->pid = fork();
	if (ptoken->pid < 0)
		error_handling(ERR_FKFL, EXIT_FAILURE);
	pid_token_add(&ms->pid_token, pid_token_new(ms, ptoken->pid));
	if (!ptoken->pid)
	{
		if (!ms->pathlist)
			error_handling_exit(ERR_PATH, 127);
		//if (ptoken->tag == 0)
			check_command(ms, ptoken);
		check_ptoken_heredoc(ptoken);
		check_ptoken_input_heredoc(ptoken);
		check_ptoken_output_fd(ptoken);
		if (execve(ms->cmd_array[0], ms->cmd_array, ms->envp) == -1)
			error_handling(ERR_EXEC, EXIT_FAILURE);
		//free_per_prompt(ms);
		//exit(0);
	}
	else
		organize_fd_ptoken(ms, ptoken);
}

void	wait_children(t_ms *ms)
{
	t_pid_token	*pid_token;

	pid_token = ms->pid_token;
	while (pid_token)
	{
		waitpid(pid_token->child_pid, NULL, 0);
		pid_token = pid_token->next;
	}
}

void	execute_last_child(t_ms *ms, t_parser_token *ptoken)
{
	int	status;

	ptoken->pid = fork();
	if (ptoken->pid < 0)
		error_handling(ERR_FKFL, EXIT_FAILURE);
	pid_token_add(&ms->pid_token, pid_token_new(ms, ptoken->pid));
	if (!ptoken->pid)
	{
		if (!ms->pathlist)
			error_handling_exit(ERR_PATH, 127);
		//if (ptoken->tag == 0)
			check_command(ms, ptoken);
		check_ptoken_heredoc(ptoken);
		check_ptoken_input_heredoc(ptoken);
		check_ptoken_output_fd(ptoken);
		check_if_builtin(ms, ptoken);
		if (execve(ms->cmd_array[0], ms->cmd_array, ms->envp) == -1)
			error_handling(ERR_EXEC, EXIT_FAILURE);
		//free_per_prompt(ms);
		//exit(0);
	}
	else
	{
		waitpid(ptoken->pid, NULL, 0);
		if (parser_token_count(ms->parser_token) > 1)
			close (ms->tube[ptoken->token_id - 2]);
		//waitpid(0, NULL, 0);
		if (parser_token_count(ms->parser_token) > 1)
		{
			dup2(ms->tube[ptoken->token_id - 3], STDIN_FILENO);
			close(ms->tube[ptoken->token_id - 3]);
		}
		if (ptoken->is_input)
			close (ptoken->input_fd);
		wait_children(ms);
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
		//export last command 
	}
}
void	token_child(t_ms *ms, t_parser_token *ptoken)
{
	free(ms->cmd_array);
	ms->cmd_array = NULL;
	if (ptoken->tag == 0)
		create_array(ms, ptoken->lxr_list);
	execute_child(ms, ptoken);
}

void	token_last_child(t_ms *ms, t_parser_token *ptoken)
{
	free(ms->cmd_array);
	ms->cmd_array = NULL;
	if (ptoken->tag == 0)
		create_array(ms, ptoken->lxr_list);
	execute_last_child(ms, ptoken);
}

/* 
 * In Bash manual:
 *	[Simple Commands], the shell executes the command directly, without 
 *	invoking another program.
 *	[Pipelines], each command in a pipeline is executed in its own subshell.
 *	Builtin commands that are invoked as part of a pipeline are also executed 
 *	in a subshell environment. Changes made to the subshell environment cannot 
 *	affect the shell’s execution environment.
 *
 * if	-> execute way pipelines
 * else	-> execute simple command:
 * 		0 is command ## 1 is builtin, ## i'm thinkng 2 could be local var
 */
void	executing_token(t_ms *ms, t_parser_token *ptoken)
{
	if (parser_token_count(ms->parser_token) > 1)
	{
		if (parser_token_last(ms->parser_token)->token_id != ptoken->token_id)
			token_child(ms, ptoken);
		else
			token_last_child(ms, ptoken);
	}
	else
	{
		if (ptoken->tag == 1)
			execute_builtin(ms, ptoken, ptoken->lxr_list);
		else if (ptoken->tag == 2)
			execute_export(ms, ptoken->lxr_list);
		else
		{
			create_array(ms, ptoken->lxr_list);
			execute_simple(ms, ptoken);
		}
	}
}

/*
 * This function assigns ms->tube[0-1] to ms->ouput_fd/input_fd
 */
void	token_piping(t_ms *ms, t_parser_token *ptoken)
{
	(void)ms;
	if (ptoken->next && ptoken->next->lxr_list->tag_pipe)
		ptoken->output_fd = ms->tube[ptoken->token_id];
	if (ptoken->prev && ptoken->prev->lxr_list->tag_pipe)
		ptoken->input_fd = ms->tube[ptoken->token_id - 1];
}

/*
 * This function resets to default the fd 0 and 1
 */
void reset_fds(t_ms *ms)
{
	dup2(ms->dflt_input, STDIN_FILENO);
	dup2(ms->dflt_output, STDOUT_FILENO);
}

/*
 * This function is the execution orchestrator
 */
void	parsing_to_executing(t_ms *ms)
{
	t_parser_token	*ptmp;

	if (parser_token_count(ms->parser_token) > 1)
		ms->tube = malloc(sizeof(int) * (parser_token_count(ms->parser_token) - 1));
	ptmp = ms->parser_token;
	set_signal_action(SIGEXE);
	while (ptmp)
	{
		if (ptmp->token_id % 2 == 1)
		{
			if (parser_token_count(ms->parser_token) > 1 && ptmp->token_id != parser_token_last(ptmp)->token_id)
			{
				if ((int)ptmp->token_id != parser_token_count(ms->parser_token))
					pipe(&ms->tube[ptmp->token_id - 1]);
				token_piping(ms, ptmp);
			}
			if (check_redirs(ptmp))
				break ;
			executing_token(ms, ptmp);
		}
		ptmp = ptmp->next;
	}
	free_per_prompt(ms);
	reset_fds(ms);
}
