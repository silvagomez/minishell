
#include "minishell.h"

/*
 * This builtin is U2U, displays all var of minishell in asc order.
 */
int	ft_declare(t_ms *ms)
{
	t_envlst	*sorted_envlst;
	t_envlst	*tmp;

	sorted_envlst = NULL;
	sorted_envlst = get_sorted_envlst(ms->envlst);
	tmp = sorted_envlst;
	i = 1;
	while (sorted_envlst)
	{
		printf("%s=", sorted_envlst->name);
		if (sorted_envlst->content)
			printf("%s\n", sorted_envlst->content);
		sorted_envlst = sorted_envlst->next;
	}
	free_sorted_envlst(tmp);
	return (0);
}
