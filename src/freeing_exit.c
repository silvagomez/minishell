
#include "minishell.h"

void	free_lexer_token(t_lexer_token *list)
{
	t_lexer_token	*next;

	next = list;
	while (list)
	{
		next = list->next;
		free (list->arg);
		free (list);
		list = next;
	}
}

void	free_exit(t_ms *ms)
{
	t_envlst	*tmp;

	free(ms->pwd_ppt);
	free(ms->pwd);
	free(ms->user);
	free(ms->home);
	free(ms->shadow);
	tmp = ms->envlst;
	while (tmp)
	{
		tmp = ms->envlst->next;
		free (ms->envlst->name);
		free (ms->envlst->content);
		free (ms->envlst);
		ms->envlst = tmp;
	}
	free_lexer_token(ms->lexer_token);
}
