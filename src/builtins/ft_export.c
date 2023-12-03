
#include "minishell.h"

/*
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

t_envlst	*dup_envlst(t_envlst *envlst)
{
	t_envlst	*dup_lst;

	if (!envlst)
		return (NULL);
	printf("ENTRO a dup_envlst\n");
	dup_lst = NULL;
	while (envlst)
	{
		dup_envlst_add(&dup_lst, dup_envlst_new(&dup_lst, envlst));
		envlst = envlst->next;
	}
	/*
	while(dup_lst)
	{
		dup_lst = dup_lst->next;
	}
	*/
	return (dup_lst);
}

void	print_test(t_envlst *envlst)
{
	t_envlst *lst;

	if (!envlst)
		printf("OJO\n");
	lst = envlst;
	while(lst)
	{
		printf(RED"CONTENIDO %s\n", lst->name);
		lst = lst->next;
	}
}
/*
 *
 */
t_envlst	*get_order_envlst(t_envlst *envlst)
{
	t_envlst	*srtd_envlst;
	t_envlst	*tmp0;
	t_envlst	*tmp1;
	t_envlst	*tmp2;

	tmp0 = dup_envlst(envlst);
	tmp1 = tmp0;
	while (tmp1->next)
	{
		tmp2 = tmp1->next;
		while (tmp1 && tmp2)
		{
			//int i = ft_strncmp(tmp1->name, tmp2->name, ft_strlen(tmp1->name));
			//printf(GRN"diferencia de %i\n"RST, i );
			if (ft_strncmp(tmp1->name, tmp2->name, ft_strlen(tmp1->name)) < 0)
			{
				/*
				printf("ft_strncmp env\n");
				printf("tmp1->name: %s\n", tmp1->name);
				printf("tmp2->name: %s\n", tmp2->name);
				*/
				tmp2 = tmp1;
			}
			tmp1 = tmp1->next;
		}
		//printf(RED"############SALIDA BUCLE 2############\n"RST);
		printf(CYN"tmp2->name %s\n"RST, tmp2->name);
		dup_envlst_add(&srtd_envlst, dup_envlst_new(&srtd_envlst, tmp2));
		printf("muevo punteros\n");
		if (tmp2->prev)
			tmp2->prev->next = tmp2->next;
		else
		{
			tmp2->next->prev = NULL;
			printf("HOLA SOY EL PRIMERO\n");
			tmp0 = tmp2->next;
		}
		if (tmp2->next)
			tmp2->next->prev = tmp2->prev;
		else
			tmp2->prev->next = NULL;
		if (tmp2)
		{

			free(tmp2->name);
			printf("libero name\n");
			free(tmp2->content);
			printf("libero content\n");
			free(tmp2);
			printf("libero tmp2\n");
			tmp2 = NULL;
		}
		printf("salgo de muevo punteros\n");
		print_test(tmp0);
		printf(HCYN"srtd_envlst->name %s\n"RST, srtd_envlst->name);
		tmp1 = tmp0;
		if(tmp1)
			printf("tmp1 existe \n");
		else
			printf("tmp1 NO existe\n");
		if(tmp1->prev != NULL)
			printf("tmp1->prev existe\n");
		else
			printf("tmp1->prev NO existe\n");
		if(tmp1->next != NULL)
			printf("tmp1->next existe\n");
		else
			printf("tmp1->next NO existe\n");
		b++;
	}
	printf("b = %i\n", b);
	return (srtd_envlst);
}

/*
 *
 */
void	display_sort_env(t_ms *ms)
{
	t_envlst	*srtd_envlst;
	int			i;

	printf("ENTRO a display sort env\n");
	srtd_envlst = NULL;
	srtd_envlst = get_order_envlst(ms->envlst);
	i = 1;
	while (srtd_envlst)
	{
		printf("%i declare -x- %s\n", i, srtd_envlst->name);
		i++;
		srtd_envlst = srtd_envlst->next;
	}
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
				return;
			}
			tmp = tmp->next;
		}

		envlst_add(&ms->envlst, envlst_new(ms, arg));
		free (var_name);
		free (content);
	}
}
