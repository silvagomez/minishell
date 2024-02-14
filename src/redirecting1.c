
#include "minishell.h"

int	redir_input_else(t_parser_token *pt, t_lexer_token *lt, \
		t_lexer_token **rt, t_lexer_token **rtn)
{
	pt->is_input = 1;
	*rt = lt;
	*rtn = lt->next;
	if (pt->input_fd != 0)
		close(pt->input_fd);
	if (lt->tag_redir == 1)
		pt->input_fd = open (lt->next->arg, O_RDONLY);
	if (lt->tag_redir == 2)
	{
		pt->is_here_doc = 1;
		hdlst_add(&(pt->hd_list), hdlst_new(lt->next->arg));
	}
	if (pt->input_fd == -1)
		return (error_handling(ERR_DFLT, EXIT_FAILURE), 1);
	return (0);
}

//redir = 1 '<' && redir = 2 '<<'
int	check_redir_input(t_parser_token *ptoken)
{
	t_lexer_token	*ltoken;
	t_lexer_token	*redir_token;
	t_lexer_token	*redir_token_next;

	ltoken = ptoken->lxr_list;
	redir_token = NULL;
	redir_token_next = NULL;
	while (ltoken)
	{
		if (ltoken->tag_redir == 1 || ltoken->tag_redir == 2)
		{
			if (!ltoken->next)
				return (error_handling(ERR_RDIR, 258), 1);
			else if (redir_input_else(ptoken, ltoken, &redir_token, \
						&redir_token_next))
				return (EXIT_FAILURE);
			ltoken = ltoken->next->next;
			del_lexer_token(ptoken, redir_token_next);
			del_lexer_token(ptoken, redir_token);
		}
		else
			ltoken = ltoken->next;
	}
	return (0);
}

void	dump_input(t_parser_token *ptoken)
{
	if (ptoken->is_here_doc)
	{
		manage_heredoc(ptoken);
		//ft_putchar_fd('\n', 1);
	}
}

int	check_redirs(t_parser_token *ptoken)
{
	if (check_redir_output(ptoken))
		return (1);
	if (check_redir_input(ptoken))
		return (1);
	dump_input(ptoken);
	return (0);
}
