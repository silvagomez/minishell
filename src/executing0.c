
#include "minishell.h"


/*
 * THIS FUNC WILL BE MOVED TO envp0 and should be invoke inside the while loop
 * due to PATH can be updated during the execution of conchita.
 */
void	env_to_path(t_ms *ms, t_envlst *envlst)
{
	int		i;
	char	*str;
	char	*tmp;

	/* January 4 I realized that should not write the func again XD
	t_envlst	*node;

	node = find_env(ms, "PATH");
	if (!node || !node->content[0])
		return (ERROR no existe PATH ó PATH no tiene contenido);
	str = ft_strdup(node->content);
	 */
	while (envlst)
	{
		if (ft_strncmp("PATH", envlst->name, 5) == 0)
		{
			str = ft_strdup(envlst->content);
			break ;
		}
		else
			envlst = envlst->next;
	}
	ms->pathlist = ft_split (str, ':');
	i = 0;
	while (ms->pathlist[i])
	{
		tmp = ms->pathlist[i];
		ms->pathlist[i] = ft_strjoin(tmp, "/");
		free(tmp);
		i++;
	}
	free(str);
}

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
	{
		free_per_prompt(ms);
		free_per_instance(ms);
		exit(1);
	}
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

void	execute_program(t_ms *ms, t_parser_token *ptoken)
{
    int		pid;

	pid = fork();
	if (!pid)
	{
		if (get_command(ms, ptoken))
		{
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
			if (execve(ms->cmd_array[0], ms->cmd_array, ms->envp) == -1)
				printf(HRED"¡EJECUCIÓN FALLIDA DE %s!"RST"\n", ms->cmd);
			free_per_prompt(ms);
			exit(0);
		}
		else
			printf("COMANDO %s NO ENCONTRADO\n", ptoken->lxr_list->arg);
	}
	else
	{
		if (parser_token_count(ms->parser_token) > 1)
			close (ms->tube[ptoken->token_id]);
		waitpid(pid, NULL, 0);
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

void	execute_program_camilo(t_ms *ms, t_parser_token *ptoken)
{
    int		pid;

	pid = fork();
	if (!pid)
	{
		if (ptoken->tag == 0)
		{
			if (!get_command(ms, ptoken))
			{
				printf("COMANDO %s NO ENCONTRADO\n", ptoken->lxr_list->arg);
				exit(127);
			}
		}
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
		waitpid(pid, NULL, 0);
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
void	execute_local_var(t_ms *ms, t_lexer_token *lxr_list)
{
	t_lexer_token	*tmp;
	size_t			not_declare;

	if (lexer_token_count(ltoken) == 1)
		execute_export(ms, lxr_list);
	tmp = lxr_list;
	not_declare = 0;
	while (tmp)
	{
		if (!is_local_var(tmp->arg))
		{
			not_declare = 1;
			break;
		}
		tmp = tmp->next;
	}
	if (not_declare = 0)
		execute_export(ms, lxr_list);
	else
	{
		if (is_builtin(ms, tmp->arg))

	}

}
*/

/* DONT DELETE IT WORKS AS GUIDE FOR ME ;)
void	execute_token(t_ms *ms, t_parser_token *token)
{
	//static int i = 1;
	//printf(HGRN"__--EXECUTION #%i--__\nINPUT_FD: %i\nOUTPUT_FD: %i\n"RST"\n", i++, token->input_fd, token->output_fd);
	//set_signal_action(SIGEXE);
    if (is_builtin(token->lxr_list->arg))
        execute_builtin(ms, token, token->lxr_list);
	else if (is_local_export(token->lxr_list->arg) && !get_command(ms, token))
		execute_export(ms, token->lxr_list);
    else
    {
        create_array(ms, token->lxr_list);
        execute_program(ms, token);
    }
	if (token->is_output)
		close (token->output_fd);
}
*/

/*
 * In Bash manual:
 *	[Simple Commands], the shell executes the command directly, without 
 *	invoking another program.
 *	[Pipelines], each command in a pipeline is executed in its own subshell.
 *	Builtin commands that are invoked as part of a pipeline are also executed 
 *	in a subshell environment. Changes made to the subshell environment cannot 
 *	affect the shell’s execution environment.
 */
void	executing_token(t_ms *ms, t_parser_token *ptoken)
{
	//execute way pipelines
	if (parser_token_count(ms->parser_token) > 1)
	{
		if (ptoken->tag == 0)
			create_array(ms, ptoken->lxr_list);
		execute_program_camilo(ms, ptoken);

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
			execute_program(ms, ptoken);
		}
	}
}
