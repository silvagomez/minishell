
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
			node->scope = scope;
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
		//si no tiene = y no existe crea var name pero sin =,
		//si esxite la variable y arg no tiene = no hace nada, no actualiza
		node = find_env(ms, arg);
		if (!node)
			//añadir un nodo sin content
			envlst_add(&ms->envlst, envlst_new(ms, arg));
	}
	/*
	tmp = ms->envlst;
	while (tmp)
	{
		if (!ft_strncmp(var_name, tmp->name, ft_strlen(var_name) + 1))
		{
			free (tmp->content);
			tmp->content = content;
			free (var_name);
			return ;
		}
		tmp = tmp->next;
	}
	envlst_add(&ms->envlst, envlst_new(ms, arg));
	*/
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
		//while (ltoken)
		//{
			// We need control, env var can only start by alpha and _
			if (err_arg(arg))
			{
				//if (err_arg(ltoken->arg))
				ft_putendl_fd("ERRRRRORRR EXPORT", 2);
				return (1);
			}
			else
			{
				//export_to_envlst(ms, ltoken->arg);
				export_to_envlst(ms, arg, scope);
				//ft_printf(RED"control\n"RST);
				//ft_printf(HBLU"ms->envp pointer %p\n"RST, ms->envp);
				//print_test_env(ms->envp);
				//print_envlst_test(ms->envlst);
				/*
				int idx = -1;
				while (ms->envp[++idx])
					printf("contenido de envp[%i] es %s\n", idx, ms->envp[idx]);
				*/
				free_string_array(ms->envp);
				//ft_printf(RED"control end\n"RST);
				//need refactor due to the = 
				envlist_to_array(ms, EXPORT);
				return (0);
			}
			//ltoken = ltoken->next;
		//}
	}
}
