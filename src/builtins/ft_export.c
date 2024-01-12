
#include "minishell.h"


/*
 * This is a test for debug.
 */
void	print_test(t_envlst *envlst)
{
	t_envlst	*lst;

	if (!envlst)
		printf("!!!!!\n");
	lst = envlst;
	while (lst)
	{
		printf(RED"NAME %s\n", lst->name);
		lst = lst->next;
	}
}

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
	else if (node->scope == 2 && scope == 2)
		return (scope);
	else if (node->scope == 1 && scope == 2)
		return (0);
	return (scope);
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
			//revisar el content dede ser =""
			envlst_add(&ms->envlst, envlst_new(ms, arg));
			envlst_last(ms->envlst)->scope = scope;
		}
		free (var_name);
	}
	else
	{
		node = find_env(ms, arg);
		if (!node)
			//añadir un nodo sin content scope 1
			envlst_add(&ms->envlst, envlst_new(ms, arg));
		else
		{
			if (node->has_equal)
				node->scope = 0;
		}	
	}
}

/*
static void	print_test_env(char **envp)
{
	size_t idx = 0;
	while(envp[idx])
	{
		printf("%lu contenido = %s\n",idx, envp[idx]);
		idx++;
	}
}
*/

/*
static void	print_envlst_test(t_envlst *node)
{
	while (node)
	{
		printf(YEL"prev %p ### %p %s %s ## next %p\n"RST, node->prev, node, node->name, node->content, node->next);
		node = node->next;
	}
}
*/

int	err_arg(char *arg)
{
	if (!ft_isalpha(*arg) && *arg != '_')
		return (1);
	return (0);
}

/*
 * This builtin whitout *ltoken: displays *envlist in asc name order,
 * whit *ltoken add a new env_node to *envlist.
 */
//void	ft_export(t_ms *ms, t_lexer_token *ltoken)
int	ft_export(t_ms *ms, char *arg, size_t scope)
{
	if (!arg)
	{
		display_sort_env(ms);
		return (0);
	}
	else
	{
		if (err_arg(arg))
		{
			ft_putendl_fd("ERRRRRORRR EXPORT", 2);
			return (1);
		}
		else
		{
			//export_to_envlst(ms, ltoken->arg);
			export_to_envlst(ms, arg, scope);
			//print_test_env(ms->envp);
			//print_envlst_test(ms->envlst);
			free_string_array(ms->envp);
			//need refactor due to the = 
			envlist_to_array(ms, EXPORT);
			return (0);
		}
	}
}
