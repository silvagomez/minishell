
#include "minishell.h"

/*
 * This function returns the size of envlst.
 */
int	envlst_node_count(t_envlst	*lst)
{
	t_envlst	*tmp;
	int			size;

	size = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}

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
		dup_envlst_last(*dup_lst)->next = new_node;
	else
		*dup_lst = new_node;
}

/*
 * This functions creates a new node (dup) of envlst
 */
t_envlst	*dup_envlst_new(t_envlst **dup_lst, t_envlst *envlst)
{
	t_envlst	*node;

	node = (t_envlst *)ft_calloc(1, sizeof(t_envlst));
	if (!node)
		return (NULL);
	node->name = ft_strdup(envlst->name);
	node->content = ft_strdup(envlst->content);
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

	if (!envlst)
		return (NULL);
	dup_lst = NULL;
	while (envlst)
	{
		dup_envlst_add(&dup_lst, dup_envlst_new(&dup_lst, envlst));
		envlst = envlst->next;
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
t_envlst	*get_order_envlst(t_envlst *envlst)
{
	t_envlst	*srtd_envlst;
	t_envlst	*tmp0;
	t_envlst	*tmp1;
	t_envlst	*tmp2;

	tmp0 = dup_envlst(envlst);
	srtd_envlst = NULL;
	tmp1 = tmp0;
	while (tmp1->next)
	{
		tmp2 = tmp1->next;
		while (tmp1 && tmp2)
		{
			if (ft_strncmp(tmp1->name, tmp2->name, ft_strlen(tmp1->name)) < 0)
				tmp2 = tmp1;
			tmp1 = tmp1->next;
		}
		dup_envlst_add(&srtd_envlst, dup_envlst_new(&srtd_envlst, tmp2));
		memory_address_relocation(&tmp2, &tmp0);
		free_env_node(&tmp2);
		tmp1 = tmp0;
		if (tmp1->next == NULL)
			dup_envlst_add(&srtd_envlst, dup_envlst_new(&srtd_envlst, tmp1));
	}
	return (free_env_node(&tmp1), srtd_envlst);
}

/*
 * This functions frees the srtd_envlst;
 */
void	free_srtd_envlst(t_envlst *tmp)
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
	t_envlst	*srtd_envlst;
	t_envlst	*tmp;
	int			i;

	srtd_envlst = NULL;
	srtd_envlst = get_order_envlst(ms->envlst);
	tmp = srtd_envlst;
	i = 1;
	while (srtd_envlst)
	{
		printf("%i declare -x %s=", i, srtd_envlst->name);
		printf("\"%s\"\n", srtd_envlst->content);
		i++;
		srtd_envlst = srtd_envlst->next;
	}
	free_srtd_envlst(tmp);
}

/*
 * This builtin whitout *arg displays *envlist in asc name order,
 * wiht *arg a new env variable will be added to *envlist.
 */
void	ft_export(t_ms *ms, char *arg)
{
	t_envlst	*tmp;
	char		*var_name;
	char		*content;

	if (!arg)
		display_sort_env(ms);
	else
	{
		// We need control, env var can only start by alpha and _
		if (!ft_isalpha(*arg) && *arg != '_')
			ft_putendl_fd("ERRRRRORRR EXPORT", 2);
		else
		{
			var_name = ft_substr(arg, 0, (ft_strchr(arg, '=') - arg));
			content = ft_strdup(ft_strchr(arg, '=') + 1);
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
			free (var_name);
			free (content);
		}
	}
}
