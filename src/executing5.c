
#include "minishell.h"

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
		status = 0;
	return (status);
}

//if (is_builtin_allowed_pipelines(ptoken->lxr_list))
void	check_if_builtin(t_ms *ms, t_parser_token *ptoken)
{
	int	status;

	if (ptoken->tag > 0)
	{
		status = execute_builtin_pipelines(ms, ptoken->lxr_list);
		exit(status);
	}
}
