
#include "minishell.h"

/*
 * This builtin is U2U, displays all var of minishell in asc order.
 */
int	ft_declare(t_ms *ms, t_lexer_token *ltoken)
{
	t_envlst	*sorted_envlst;
	t_envlst	*tmp;

	if (ltoken->next)
		return (error_handling(ERR_IBOP, EXIT_FAILURE), 1);
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
		sorted_envlst = sorted_envlst->next;
	}
	free_sorted_envlst(tmp);
	return (0);
}
