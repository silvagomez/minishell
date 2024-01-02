
#include "minishell.h"

/*
 * This functions returns the last node of the list.
 */
t_envlst	*dup_envlst_last(t_envlst *dup_lst)
{
	if (!dup_lst)
		return (NULL);
	while (dup_lst->next != NULL)
		dup_lst = dup_lst->next;
	return (dup_lst);
}

/*
 * This functions adds a node into the dup list of envlst.
 */
void	dup_envlst_add(t_envlst **dup_lst, t_envlst *new_node)
{
	if (!new_node)
		return ;
	if (*dup_lst != NULL)
	{
		new_node->prev = dup_envlst_last(*dup_lst);
		new_node->next = NULL;
		dup_envlst_last(*dup_lst)->next = new_node;
	}
	else
	{
		*dup_lst = new_node;
		new_node->prev = NULL;
		new_node->next = NULL;
	}
}

/*
 * This functions creates a new node (dup) of envlst
 */
t_envlst	*dup_envlst_new(t_envlst **dup_lst, t_envlst *envlst_node)
{
	t_envlst	*node;

	node = (t_envlst *)ft_calloc(1, sizeof(t_envlst));
	if (!node)
		return (NULL);
	node->name = ft_strdup(envlst_node->name);
	if (envlst_node->has_equal)
		node->content = ft_strdup(envlst_node->content);
	else
		node->content = NULL;
	node->has_equal = envlst_node->has_equal;
	node->scope = envlst_node->scope;
	node->prev = dup_envlst_last(*dup_lst);
	node->next = NULL;
	return (node);
}

/*
 * This functions returns a *duplist of envlst.
 */
t_envlst	*dup_envlst(t_envlst *envlst)
{
	t_envlst	*dup_lst;
	t_envlst	*envlst_node;

	if (!envlst)
		return (NULL);
	dup_lst = NULL;
	envlst_node = envlst;
	while (envlst_node)
	{
		dup_envlst_add(&dup_lst, dup_envlst_new(&dup_lst, envlst_node));
		envlst_node = envlst_node->next;
	}
	return (dup_lst);
}

/*
 * This is a test for debug.
 */
void	print_test(t_envlst *envlst)
{
	t_envlst	*lst;

	if (!envlst)
		printf("OJO\n");
	lst = envlst;
	while (lst)
	{
		printf(RED"CONTENIDO %s\n", lst->name);
		lst = lst->next;
	}
}

/*
 * This function relocates *next and *prev of tmp2 after been duplicated and 
 * added to strd_envlst, thus free tmp2.
 */
void	memory_address_relocation(t_envlst **tmp2, t_envlst **tmp0)
{
	if ((*tmp2)->prev)
		(*tmp2)->prev->next = (*tmp2)->next;
	else
	{
		(*tmp2)->next->prev = NULL;
		(*tmp0) = (*tmp2)->next;
	}
	if ((*tmp2)->next)
		(*tmp2)->next->prev = (*tmp2)->prev;
	else
		(*tmp2)->prev->next = NULL;
}

/*
 * This functions frees a node.
 */
void	free_env_node(t_envlst	**tmp2)
{
	if (*tmp2)
	{
		free((*tmp2)->name);
		free((*tmp2)->content);
		free(*tmp2);
		*tmp2 = NULL;
	}
}

/*
* This function returns *duplst sorted by asc name.
*/
t_envlst	*get_sorted_envlst(t_envlst *envlst)
{
	t_envlst	*sorted_envlst;
	//t_envlst	*srtd_envlst;
	t_envlst	*tmp0;
	t_envlst	*tmp1;
	t_envlst	*tmp2;

	tmp0 = dup_envlst(envlst);
	sorted_envlst = NULL;
	//srtd_envlst = NULL;
	tmp1 = tmp0;
	ft_printf(RED"controlx2\n"RST);
	while (tmp1->next)
	{
		tmp2 = tmp1->next;
		while (tmp1 && tmp2)
		{
			if (ft_strncmp(tmp1->name, tmp2->name, ft_strlen(tmp1->name)) < 0)
				tmp2 = tmp1;
			tmp1 = tmp1->next;
		}
		//dup_envlst_add(&srtd_envlst, dup_envlst_new(&srtd_envlst, tmp2));
		memory_address_relocation(&tmp2, &tmp0);
		dup_envlst_add(&sorted_envlst, tmp2);
		ft_printf(RED"controlx3\n"RST);
		//free_env_node(&tmp2);
		tmp1 = tmp0;
		if (tmp1->next == NULL)
			//dup_envlst_add(&srtd_envlst, dup_envlst_new(&srtd_envlst, tmp1));
			dup_envlst_add(&sorted_envlst, tmp1);
	}
	//return (free_env_node(&tmp1), srtd_envlst);
	return (sorted_envlst);
}

/*
 * This functions frees the srtd_envlst;
 */
void	free_sorted_envlst(t_envlst *tmp)
{
	t_envlst	*node;

	//Needs debug, i'm not doing well the free :( i'm having direct leak
	while (tmp)
	{
		node = tmp->next;
		free_env_node(&tmp);
		tmp = node;
	}
}

/*
 * This functions prints the envlist sorted by asc name.
 */
void	display_sort_env(t_ms *ms)
{
	t_envlst	*sorted_envlst;
	t_envlst	*tmp;
	int			i;

	sorted_envlst = NULL;
	sorted_envlst = get_sorted_envlst(ms->envlst);
	tmp = sorted_envlst;
	i = 1;
	while (sorted_envlst)
	{
		//delete i
		if (sorted_envlst->has_equal)
		{
			printf("\"%lu\"\n", sorted_envlst->has_equal);
			printf("%i declare -x %s=", i, sorted_envlst->name);
			printf("\"%s\"\n", sorted_envlst->content);
		}
		else
			printf("%i declare -x %s\n", i, sorted_envlst->name);
		i++;
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
void	ft_export(t_ms *ms, char *arg, size_t scope)
{
	if (!arg)
	{
	//if (!ltoken)
		ft_printf(RED"control\n"RST);
		display_sort_env(ms);
	//	print_envlst_test(ms->envlst);
	}
	else
	{
		//while (ltoken)
		//{
			// We need control, env var can only start by alpha and _
			if (err_arg(arg))
			//if (err_arg(ltoken->arg))
				ft_putendl_fd("ERRRRRORRR EXPORT", 2);
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
			}
			//ltoken = ltoken->next;
		//}
	}
}
