
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
	while (sorted_envlst)
	{
		if (sorted_envlst->content)
		{
			printf("%s=", sorted_envlst->name);
			printf("%s\n", sorted_envlst->content);
		}
		// test in macos 42 if export variables without content are printed?
		/*
		else
			printf("%s\n", sorted_envlst->name);
		*/
		sorted_envlst = sorted_envlst->next;
	}
	free_sorted_envlst(tmp);
	return (0);
}
