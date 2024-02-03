
#include "minishell.h"

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
	ms->cmd_array[i] = 0;
}

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

int	execute_builtin(t_ms *ms, t_parser_token *ptoken, t_lexer_token *ltoken)
{
	int	status;
	(void)ms;

	status = 1;
	if (!ft_strncmp(ltoken->arg, "echo", ft_strlen(ltoken->arg) + 1))
		status = ft_echo(ltoken->next);
		//status = ft_echo(ms, ptoken, ltoken->next);
	else if (!ft_strncmp(ltoken->arg, "cd", ft_strlen(ltoken->arg) + 1))
		status = ft_cd(ms, ltoken);
	else if (!ft_strncmp(ltoken->arg, "pwd", ft_strlen(ltoken->arg) + 1))
		status = ft_pwd(ms);
	else if (!ft_strncmp(ltoken->arg, "export", ft_strlen(ltoken->arg) + 1))
		status = execute_export(ms, ltoken);
	else if (!ft_strncmp(ltoken->arg, "unset", ft_strlen(ltoken->arg) + 1))
		status = execute_unset(ms, ltoken);
	else if (!ft_strncmp(ltoken->arg, "env", ft_strlen(ltoken->arg) + 1))
		status = ft_env(ms);
	else if (!ft_strncmp(ltoken->arg, "declare", ft_strlen(ltoken->arg) + 1))
	{
		if (ltoken->next == NULL)
			status = ft_declare(ms);
	}
	else if (!ft_strncmp(ltoken->arg, "exit", ft_strlen(ltoken->arg) + 1))
		ft_exit(ms, ltoken->next);
	if (parser_token_count(ms->parser_token) > 1)
			close (ms->tube[ptoken->token_id]);
	if (parser_token_count(ms->parser_token) > 1)
	{
		dup2(ms->tube[ptoken->token_id - 1], STDIN_FILENO);
		close(ms->tube[ptoken->token_id - 1]);
	}
	if (ptoken->is_input)
		close (ptoken->input_fd);
	return (status);
}

void	execute_simple(t_ms *ms, t_parser_token *ptoken)
{
    int		pid;
	int		status;

	pid = fork();
	if (!pid)
	{
		if (!ms->pathlist)
			error_handling_exit(ERR_PATH, 127);
		if (get_command(ms, ptoken))
		{
			if (ptoken->is_here_doc)
			{
				printf("A\n");
				ptoken->input_fd = dup(ptoken->hd_pipe[0]);
				close (ptoken->hd_pipe[0]);
			}
			if(ptoken->is_input || ptoken->is_here_doc)
			{
				printf("B\n");
				dup2(ptoken->input_fd, STDIN_FILENO);
				close (ptoken->input_fd);
			}
			if (ptoken->output_fd > 2)
			{
				printf("C\n");
				dup2(ptoken->output_fd, STDOUT_FILENO);
				close (ptoken->output_fd);
			}
			if (execve(ms->cmd_array[0], ms->cmd_array, ms->envp) == -1)
				printf(HRED"¡EJECUCIÓN FALLIDA DE %s!"RST"\n", ms->cmd);
			free_per_prompt(ms);
			//exit(0);
		}
		else
			printf("COMANDO %s NO ENCONTRADO\n", ptoken->lxr_list->arg);
	}
	else
	{
		if (parser_token_count(ms->parser_token) > 1)
			close (ms->tube[ptoken->token_id]);
		if (parser_token_last(ptoken)->token_id == parser_token_last(ms->parser_token)->token_id)
			ft_printf("TESTING\n");
		waitpid(pid, &status, 0);
		g_status = status;
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
}

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

int	execute_builtin_pipelines(t_ms *ms, t_lexer_token *ltoken)
{
	int	status;

	status = 1;
	if (!ft_strncmp(ltoken->arg, "echo", ft_strlen(ltoken->arg) + 1))
		status = ft_echo(ltoken->next);
	else if (!ft_strncmp(ltoken->arg, "pwd", ft_strlen(ltoken->arg) + 1))
		status = ft_pwd(ms);
	else if (!ft_strncmp(ltoken->arg, "env", ft_strlen(ltoken->arg) + 1))
		status = ft_env(ms);
	else if (!ft_strncmp(ltoken->arg, "export", ft_strlen(ltoken->arg) + 1))
	{
		if (ltoken->next == NULL)
			status = execute_export(ms, ltoken);
	}
	else if (!ft_strncmp(ltoken->arg, "declare", ft_strlen(ltoken->arg) + 1))
	{
		if (ltoken->next == NULL)
			status = ft_declare(ms);
	}
	return (status);
}

void	check_command(t_ms *ms, t_parser_token *ptoken)
{
	if (!get_command(ms, ptoken))
			{
				printf("COMANDO %s NO ENCONTRADO\n", ptoken->lxr_list->arg);
				exit(127);
			}
}

void	execute_program(t_ms *ms, t_parser_token *ptoken)
{
	ptoken->pid = fork();
	if (ptoken->pid < 0)
		ft_putendl_fd("ERRORR and returnn", 2);
	pid_token_add(&ms->pid_token, pid_token_new(ms, ptoken->pid));
	if (!ptoken->pid)
	{
		if (ptoken->tag == 0)
		/* {
			if (!get_command(ms, ptoken))
			{
				printf("COMANDO %s NO ENCONTRADO\n", ptoken->lxr_list->arg);
				exit(127);
			}
		} */
			check_command(ms, ptoken);
		if (ptoken->is_here_doc)
		{
			ptoken->input_fd = dup(ptoken->hd_pipe[0]);
			close (ptoken->hd_pipe[0]);
		}
		if(ptoken->is_input || ptoken->is_here_doc)
		{
			dup2(ptoken->input_fd, STDIN_FILENO);
			close (ptoken->input_fd);
		}
		if (ptoken->output_fd > 2)
		{
			dup2(ptoken->output_fd, STDOUT_FILENO);
			close (ptoken->output_fd);
		}
		if (ptoken->tag > 0)
		{
			if (is_builtin_allowed_pipelines(ptoken->lxr_list))
				execute_builtin_pipelines(ms, ptoken->lxr_list);
			exit(0);
		}
		if (execve(ms->cmd_array[0], ms->cmd_array, ms->envp) == -1)
			printf(HRED"¡EJECUCIÓN FALLIDA DE CAMILO %s!"RST"\n", ms->cmd);
		free_per_prompt(ms);
		exit(0);
	}
	else
	{
		if (parser_token_count(ms->parser_token) > 1)
			close (ms->tube[ptoken->token_id]);
		//waitpid(ptoken->pid, NULL, 0);
		int n=3;
		while (n--)
			waitpid(0, NULL, 0);
		if (parser_token_count(ms->parser_token) > 1)
		{
			dup2(ms->tube[ptoken->token_id - 1], STDIN_FILENO);
			close(ms->tube[ptoken->token_id - 1]);
		}
		if (ptoken->is_input)
			close (ptoken->input_fd);
	}
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
 *	IF -> execute way pipelines
 *	ELSE -> execute simple commands
 *	is command ## 1 is builtin, ## i'm thinkng 2 could be local var
 */
void	executing_token(t_ms *ms, t_parser_token *ptoken)
{
	if (parser_token_count(ms->parser_token) > 1)
	{
		if (ptoken->tag == 0)
			create_array(ms, ptoken->lxr_list);
		execute_program(ms, ptoken);

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

void	execute_child(t_ms *ms, t_parser_token *ptoken)
{
	ptoken->pid = fork();
	if (ptoken->pid < 0)
		ft_putendl_fd("ERRORR and returnn", 2);
	pid_token_add(&ms->pid_token, pid_token_new(ms, ptoken->pid));
	if (!ptoken->pid)
	{
		if (!ms->pathlist)
			error_handling_exit(ERR_PATH, 127);
		if (ptoken->tag == 0)
	//	{
	//		if (!get_command(ms, ptoken))
	//		{
	//			printf("COMANDO %s NO ENCONTRADO\n", ptoken->lxr_list->arg);
	//			exit(127);
	//		}
	//	}
			check_command(ms, ptoken);
		if (ptoken->is_here_doc)
		{
			ptoken->input_fd = dup(ptoken->hd_pipe[0]);
			close (ptoken->hd_pipe[0]);
		}
		if(ptoken->is_input || ptoken->is_here_doc)
		{
			dup2(ptoken->input_fd, STDIN_FILENO);
			close (ptoken->input_fd);
		}
		if (ptoken->output_fd > 2)
		{
			dup2(ptoken->output_fd, STDOUT_FILENO);
			close (ptoken->output_fd);
		}
		if (ptoken->tag > 0)
		{
			if (is_builtin_allowed_pipelines(ptoken->lxr_list))
				execute_builtin_pipelines(ms, ptoken->lxr_list);
			exit(0);
		}
		if (execve(ms->cmd_array[0], ms->cmd_array, ms->envp) == -1)
			printf(HRED"¡EJECUCIÓN FALLIDA DE CAMILO %s!"RST"\n", ms->cmd);
		free_per_prompt(ms);
		exit(0);
	}
	else
	{
		if (parser_token_count(ms->parser_token) > 1)
			close (ms->tube[ptoken->token_id]);
		//waitpid(ptoken->pid, NULL, 0);
		if (parser_token_count(ms->parser_token) > 1)
		{
			dup2(ms->tube[ptoken->token_id - 1], STDIN_FILENO);
			close(ms->tube[ptoken->token_id - 1]);
		}
		if (ptoken->is_input)
			close (ptoken->input_fd);
		/*
		close(ptoken->output_fd);
		dup2(ptoken->input_fd, STDIN_FILENO);
		close(ptoken->input_fd);
		*/
	}
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
	token_piping(ms, ptoken);
	ptoken->pid = fork();
	if (ptoken->pid < 0)
		ft_putendl_fd("ERRORR and returnn", 2);
	pid_token_add(&ms->pid_token, pid_token_new(ms, ptoken->pid));
	if (!ptoken->pid)
	{
		if (!ms->pathlist)
			error_handling_exit(ERR_PATH, 127);
		if (ptoken->tag == 0)
		//{
		//	if (!get_command(ms, ptoken))
		//	{
		//		printf("COMANDO %s NO ENCONTRADO\n", ptoken->lxr_list->arg);
		//		exit(127);
		//	}
		//}
			check_command(ms, ptoken);
		if (ptoken->is_here_doc)
		{
			ptoken->input_fd = dup(ptoken->hd_pipe[0]);
			close (ptoken->hd_pipe[0]);
		}
		if(ptoken->is_input || ptoken->is_here_doc)
		{
			dup2(ptoken->input_fd, STDIN_FILENO);
			close (ptoken->input_fd);
		}
		if (ptoken->output_fd > 2)
		{
			dup2(ptoken->output_fd, STDOUT_FILENO);
			close (ptoken->output_fd);
		}
		if (ptoken->tag > 0)
		{
			if (is_builtin_allowed_pipelines(ptoken->lxr_list))
				execute_builtin_pipelines(ms, ptoken->lxr_list);
			exit(0);
		}
		if (execve(ms->cmd_array[0], ms->cmd_array, ms->envp) == -1)
			printf(HRED"¡EJECUCIÓN FALLIDA DE CAMILO %s!"RST"\n", ms->cmd);
		free_per_prompt(ms);
		exit(0);
	}
	else
	{
		waitpid(ptoken->pid, NULL, 0);
		if (parser_token_count(ms->parser_token) > 1)
			close (ms->tube[ptoken->token_id]);
		//waitpid(0, NULL, 0);
		if (parser_token_count(ms->parser_token) > 1)
		{
			dup2(ms->tube[ptoken->token_id - 1], STDIN_FILENO);
			close(ms->tube[ptoken->token_id - 1]);
		}
		if (ptoken->is_input)
			close (ptoken->input_fd);
		wait_children(ms);
		//export last command 
		/*
		waitpid(ptoken->pid, NULL, 0);
		close(ptoken->output_fd);
		dup2(ptoken->input_fd, STDIN_FILENO);
		close(ptoken->input_fd);
		wait_children(ms);
		*/
	}
}

void	executing_token_idea2(t_ms *ms, t_parser_token *ptoken)
{
	//execute way pipelines
	if (parser_token_count(ms->parser_token) > 1)
	{
		if (parser_token_last(ms->parser_token)->token_id != ptoken->token_id)
		{	
			if (ptoken->tag == 0)
				create_array(ms, ptoken->lxr_list);
			execute_child(ms, ptoken);
		}
		else
		{
			if (ptoken->tag == 0)
				create_array(ms, ptoken->lxr_list);
			execute_last_child(ms, ptoken);
		}

	}
	//execute simple commands
	else
	{
		//0 is command ## 1 is builtin, ## i'm thinkng 2 could be local var
		if (ptoken->tag == 1)
			execute_builtin(ms, ptoken, ptoken->lxr_list);
		//else if (is_local_export(ptoken->lxr_list) && !get_command(ms, ptoken))
		else if (ptoken->tag == 2)
			//execute_local_var(ms, ptoken->lxr_list);
			execute_export(ms, ptoken->lxr_list);
		else
		{
			create_array(ms, ptoken->lxr_list);
			execute_simple(ms, ptoken);
		}
	}
}
