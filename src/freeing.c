
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
	if(array)
	{
	while(array[++i])
		free(array[i]);
	free (array);
	}
}

void	free_envlst(t_envlst *envlst)
{
	t_envlst	*tmp;

	while (envlst)
	{
		tmp = envlst->next;
		free (envlst->name);
		free (envlst->content);
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
		free(ptoken->hd_line);
		free_lexer_list(ptoken->lxr_list);
		free(ptoken);
		ptoken = tmp;
	}
}

void	free_per_prompt(t_ms *ms)
{
	free_string_array(ms->cmd_array);
	free_string_array(ms->pathlist);
	free(ms->prompt);
	free(ms->rline);
	free(ms->shadow);
	free(ms->pwd);
	free(ms->pwd_ppt);
	free(ms->cmd);
	free_parser_list(ms->parser_token);
	//t_strlst		*str_lst; I BELIEVE THIS ONE IS ALREADY FREED
}

void	free_per_instance(t_ms *ms)
{
	free_string_array(ms->envp);
	free(ms->user);
	free(ms->home);
	free(ms->pid);
	free(ms->os_name);
	free_envlst(ms->envlst);
}