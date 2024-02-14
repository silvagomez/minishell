
#include "minishell.h"

void	free_string_array(char **array)
{
	int	i;

	i = -1;
	if (array)
	{
		while (array[++i])
		{
			free(array[i]);
			array[i] = NULL;
		}
	}
	free(array);
	array = NULL;
}

void	free_envlst(t_envlst *envlst)
{
	t_envlst	*tmp;

	while (envlst)
	{
		tmp = envlst->next;
		free (envlst->name);
		envlst->name = NULL;
		free (envlst->content);
		envlst->content = NULL;
		free (envlst);
		envlst = tmp;
	}
}

void	free_lexer_list(t_lexer_token *ltoken)
{
	t_lexer_token	*tmp;

	while (ltoken)
	{
		tmp = ltoken->next;
		free(ltoken->arg);
		ltoken->arg = NULL;
		free(ltoken);
		ltoken = tmp;
	}
}

void	free_parser_list(t_parser_token *ptoken)
{
	t_parser_token	*tmp;

	while (ptoken)
	{
		tmp = ptoken->next;
		free(ptoken->hd_str);
		ptoken->hd_str = NULL;
		free(ptoken->hd_line);
		ptoken->hd_line = NULL;
		free_lexer_list(ptoken->lxr_list);
		ptoken->lxr_list = NULL;
		free(ptoken);
		ptoken = tmp;
	}
}
