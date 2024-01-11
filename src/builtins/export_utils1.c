
#include "minishell.h"

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
