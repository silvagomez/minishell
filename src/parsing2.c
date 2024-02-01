
#include "minishell.h"

static const char	*g_builtin[8] = 
{
	"echo", 
	"cd", 
	"pwd", 
	"export", 
	"unset", 
	"env", 
	"exit",
	"declare"
};

size_t is_command(t_ms *ms, t_lexer_token *ltoken)
{
	size_t	idx;
	char	*cmd;

	idx = -1;
	while (ms->pathlist[++idx])
	{
		cmd = ft_strjoin(ms->pathlist[idx], ltoken->arg);
		if (access(cmd, F_OK) == 0)
			return (free(cmd), ltoken->tag_program = 1, 1);
		free(cmd);
	}
	if (ms->pathlist[idx] == NULL)
	{
		if (access(ltoken->arg, F_OK) == 0)
			return (ltoken->tag_program = 1, 1);
		else
			return (0);
	}
	return (0);
}

size_t is_builtin(t_lexer_token *ltoken)
{
    int i;

    i = -1;
    while(++i < 8)
    {
        if (!ft_strncmp(ltoken->arg, g_builtin[i], ft_strlen(ltoken->arg) + 1))
		{
			ltoken->tag_builtin = 1;
            return (1);
		}
    }
	return (0);
}

size_t	is_local_var(t_ms *ms, t_parser_token *ptoken)
{
	int				size;
	size_t			not_declare;

	(void)ms;
	t_lexer_token	*ltoken;

	size = lexer_token_count(ptoken->lxr_list);
	if (size == 1 && seek_equal(ptoken->lxr_list->arg))
	{
		if (ptoken->lxr_list->tag_double_q)
			return (0);
		else if (ptoken->lxr_list->tag_single_q)
			return (0);
		else
			return (2);
	}
	else
	{
		not_declare = 0;
		ltoken = ptoken->lxr_list;
		while (ltoken)
		{
			if (!seek_equal(ltoken->arg) || ltoken->tag_double_q || ltoken->tag_single_q)
			{
				not_declare = 1;
				break ;
			}
			ltoken = ltoken->next;
		}
		if (not_declare == 0)
			return (2);
		else if (ltoken->tag_double_q || ltoken->tag_single_q)
			return (0);
		else
		{
			remove_ltoken(ptoken, ltoken->token_id);
			if (is_builtin(ptoken->lxr_list))
				return (1);
			else
				return (0);
		}
	}
}
