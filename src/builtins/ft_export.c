
#include "minishell.h"

/*
 * This functions prints the envlist sorted by asc name.
 */
void	display_sort_env(t_ms *ms)
{
	t_envlst	*sorted_envlst;
	t_envlst	*tmp;

	sorted_envlst = NULL;
	sorted_envlst = get_sorted_envlst(ms->envlst);
	tmp = sorted_envlst;
	while (sorted_envlst)
	{
		if (sorted_envlst->scope < 2)
		{
			if (sorted_envlst->has_equal)
			{
				printf("declare -x %s=", sorted_envlst->name);
				printf("\"%s\"\n", sorted_envlst->content);
			}
			else
				printf("declare -x %s\n", sorted_envlst->name);
		}
		sorted_envlst = sorted_envlst->next;
	}
	free_sorted_envlst(tmp);
}

/*
 * Scope:
 * 0 = env;
 * 1 = export;
 * 2 = declare;
 */
size_t	define_scope(t_envlst *node, size_t scope)
{
	if (node->scope == 0 && scope == 0)
		return (scope);
	else if (node->scope == 0 && scope == 2)
		return (0);
	else if (node->scope == 2 && scope == 2)
		return (scope);
	else if (node->scope == 1 && scope == 2)
		return (0);
	return (scope);
}

/*
 * Exterior else -> if !node add node without content, scope = 1;
 * if node has equal the node will move to env = scope = 0;
 *
 */
void	export_else_case(t_ms *ms, char *arg)
{
	t_envlst	*node;

	node = find_env(ms, arg);
	if (!node)
		envlst_add(&ms->envlst, envlst_new(ms, arg));
	else
	{
		if (node->has_equal)
			node->scope = 0;
	}
}

void	export_to_envlst(t_ms *ms, char *arg, size_t scope)
{
	t_envlst	*node;
	char		*var_name;
	char		*content;

	if (ft_strchr(arg, '='))
	{
		var_name = ft_substr(arg, 0, (ft_strchr(arg, '=') - arg));
		node = find_env(ms, var_name);
		if (node)
		{
			content = ft_strdup(ft_strchr(arg, '=') + 1);
			update_env_content(ms, var_name, content);
			node->has_equal = 1;
			node->scope = define_scope(node, scope);
			free (content);
		}
		else
		{
			envlst_add(&ms->envlst, envlst_new(ms, arg));
			envlst_last(ms->envlst)->scope = scope;
		}
		free (var_name);
	}
	else
		export_else_case(ms, arg);
}

/*
 * This builtin whitout *ltoken: displays *envlist in asc name order,
 * whit *ltoken add a new env_node to *envlist.
 */
//void	ft_export(t_ms *ms, t_lexer_token *ltoken)
int	ft_export(t_ms *ms, char *arg, size_t scope)
{
	if (!arg)
		return (display_sort_env(ms), 0);
	else
	{
		if (err_arg(arg))
			return (error_handling(ERR_IBOP, EXIT_FAILURE), 1);
		else
		{
			export_to_envlst(ms, arg, scope);
			envlist_to_array(ms, EXPORT);
			return (0);
		}
	}
}
