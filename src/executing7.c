
#include "minishell.h"

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

void	export_to_declare(t_ms *ms, t_lexer_token *tmp, int *status)
{
	while (tmp)
	{
		(*status) = ft_export(ms, tmp->arg, 2);
		tmp = tmp->next;
	}
}

/*
 * Scope:
 * 0 = env;
 * 1 = export;
 * 2 = declare;
 */
int	execute_export(t_ms *ms, t_lexer_token *ltoken)
{
	t_lexer_token	*tmp;
	int				status;

	tmp = ltoken;
	if (!ft_strncmp(tmp->arg, "export", ft_strlen(tmp->arg) + 1))
	{
		if (tmp->next)
		{
			tmp = tmp->next;
			while (tmp)
			{
				status = ft_export(ms, tmp->arg, 0);
				tmp = tmp->next;
			}
		}
		else
			status = ft_export(ms, NULL, -1);
	}
	else
		export_to_declare(ms, tmp, &status);
	return (status);
}

int	execute_unset(t_ms *ms, t_lexer_token *ltoken)
{
	t_lexer_token	*tmp;
	int				status;

	if (ltoken->next)
	{
		tmp = ltoken->next;
		while (tmp)
		{
			status = ft_unset(ms, tmp->arg);
			tmp = tmp->next;
		}
	}
	else
		status = ft_unset(ms, NULL);
	return (status);
}
