
#include "minishell.h"

//This func does what free_lexer_list and free_parser_list do
/* void	free_parser_token(t_ms *ms)
{
	t_lexer_token	*ltmp;
	t_parser_token	*ptmp;

	while(ms->parser_token)
	{
		ptmp = ms->parser_token->next;
		while (ms->parser_token->lxr_list)
		{
			ltmp = ms->parser_token->lxr_list->next;
			free (ms->parser_token->lxr_list);
			ms->parser_token->lxr_list =  ltmp;
		}
		free (ms->parser_token);
		ms->parser_token = ptmp;
	}
} */

void	free_string_array(char **array)
{
	int	i;

	i = -1;
	if (array)
	{
		ft_printf(HBLU"ms->array pointer %p\n"RST, array);
		while (array[++i])
		{
			ft_printf(HBLU"ms->array[%i] pointer %p is %s\n"RST, i, array[i], array[i]);
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

void	free_per_prompt(t_ms *ms)
{
	free(ms->prompt);
	ms->prompt = NULL;
	free(ms->rline);
	ms->rline = NULL;
	free(ms->shadow);
	ms->shadow = NULL;
	free(ms->pwd_ppt);
	ms->pwd_ppt = NULL;
	/* free(ms->cmd);
	ms->cmd = NULL; */
	free_parser_list(ms->parser_token);
	ms->parser_token = NULL;
	//t_strlst		*str_lst; I BELIEVE THIS ONE IS ALREADY FREED
}

void	free_per_instance(t_ms *ms)
{
	//We should not free envp per instance att:Camilo
	//free_string_array(ms->envp);
	free_string_array(ms->pathlist);
	free(ms->pwd);
	free(ms->user);
	free(ms->home);
	free(ms->pid);
	free(ms->os_name);
	free_envlst(ms->envlst);
}
