
#include "minishell.h"

void	del_lexer_token(t_parser_token *ptoken, t_lexer_token *ltoken)
{
	if (ltoken)
	{
		if (!ltoken->prev)
		{
			if (ltoken->next)
				ltoken->next->prev = NULL;
			ptoken->lxr_list = ltoken->next;
		}
		else if (!ltoken->next)
		{
			if (ltoken->prev)
				ltoken->prev->next = NULL;
		}
		else if (ltoken->next && ltoken->prev)
		{
			ltoken->next->prev = ltoken->prev;
			ltoken->prev->next = ltoken->next;
		}
		free (ltoken->arg);
		free (ltoken);
	}
}

//redir output = 3 '>' && redir = 4 '>>'
int	redir_output_fd(t_parser_token *ptoken, t_lexer_token *ltoken)
{
	if (!ltoken->next)
		return (error_handling(ERR_RDIR, 258), 1);
	else
	{
		ptoken->is_output = 1;
		if (ptoken->output_fd != 1)
			close(ptoken->output_fd);
		if (ltoken->tag_redir == 3)
			ptoken->output_fd = open (ltoken->next->arg, \
					O_TRUNC | O_RDWR | O_CREAT, 0777);
		if (ltoken->tag_redir == 4)
			ptoken->output_fd = open (ltoken->next->arg, \
					O_APPEND | O_RDWR | O_CREAT, 0777);
		if (ptoken->output_fd == -1)
			return (error_handling(ERR_DFLT, EXIT_FAILURE), 1);
	}
	return (0);
}

//redir = 3 '>' && redir = 4 '>>'
int	check_redir_output(t_parser_token *ptoken)
{
	t_lexer_token	*ltoken;
	t_lexer_token	*redir_token;
	t_lexer_token	*redir_token_next;

	ltoken = ptoken->lxr_list;
	while (ltoken)
	{
		if (ltoken->tag_redir == 3 || ltoken->tag_redir == 4)
		{
			redir_token = ltoken;
			redir_token_next = ltoken->next;
			if (redir_output_fd(ptoken, ltoken))
				return (EXIT_FAILURE);
			ltoken = ltoken->next->next;
			del_lexer_token(ptoken, redir_token);
			del_lexer_token(ptoken, redir_token_next);
		}
		else
			ltoken = ltoken->next;
	}
	return (0);
}

int	redir_input_fd(t_parser_token *ptoken, t_lexer_token *ltoken, \
		t_lexer_token **redir_token, t_lexer_token **redir_token_next)
{
	if (!ltoken->next)
		return (error_handling(ERR_RDIR, 258), 1);
	else
	{
		ptoken->is_input = 1;
		(*redir_token) = ltoken;
		(*redir_token_next) = ltoken->next;
		if (ptoken->input_fd != 0)
			close(ptoken->input_fd);
		if (ltoken->tag_redir == 1)
			ptoken->input_fd = open (ltoken->next->arg, O_RDONLY);
		if (ltoken->tag_redir == 2)
		{
			ptoken->is_here_doc = 1;
			hdlst_add(&(ptoken->hd_list), hdlst_new(ltoken->next->arg));
		}
		if (ptoken->input_fd == -1)
			return (error_handling(ERR_DFLT, EXIT_FAILURE), 1);
	}
	return (0);
}
