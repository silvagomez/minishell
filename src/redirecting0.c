
#include "minishell.h"

void	delete_lexer_token (t_parser_token *ptoken, t_lexer_token *ltoken)
{
	if (ltoken)
	{
		if (!ltoken->prev)
		{
			if (ltoken->next)
				ltoken->next->prev = NULL;
			ptoken->lxr_list = ltoken->next;
		}
		else if(!ltoken->next)
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
				if (!ltoken->next)
					return (error_handling(ERR_RDIR, 258), 1);
				else
				{
					ptoken->is_output = 1;
					if (ptoken->output_fd != 1)
						close(ptoken->output_fd);
					if (ltoken->tag_redir == 3)
						ptoken->output_fd = open (ltoken->next->arg, O_TRUNC | O_RDWR | O_CREAT, 0777);
					if (ltoken->tag_redir == 4)
						ptoken->output_fd = open (ltoken->next->arg, O_APPEND | O_RDWR | O_CREAT, 0777);
					if(ptoken->output_fd == -1)
						return (error_handling(ERR_DFLT, EXIT_FAILURE), 1);
				}
				ltoken = ltoken->next->next;
				delete_lexer_token(ptoken, redir_token);
				delete_lexer_token(ptoken, redir_token_next);
			}
		else
			ltoken = ltoken->next;
	}
	return (0);
}

int	check_redir_input(t_parser_token *ptoken)
{
	t_lexer_token	*ltoken;
	t_lexer_token	*redir_token;
	t_lexer_token	*redir_token_next;

	ltoken = ptoken->lxr_list;
	while (ltoken)
	{
		if (ltoken->tag_redir == 1 || ltoken->tag_redir == 2)
			{
				if (!ltoken->next)
					return (error_handling(ERR_RDIR, 258), 1);
				else
				{
					ptoken->is_input = 1;
					redir_token = ltoken;
					redir_token_next = ltoken->next;
					if (ptoken->input_fd != 0)
						close(ptoken->input_fd);
					if (ltoken->tag_redir == 1)
						ptoken->input_fd = open (ltoken->next->arg, O_RDONLY);
					if (ltoken->tag_redir == 2)
					{
						ptoken->is_here_doc = 1;
						hdlst_add(&(ptoken->hd_list), hdlst_new(ltoken->next->arg));
					}
					if(ptoken->input_fd == -1)
						return (error_handling(ERR_DFLT, EXIT_FAILURE), 1);
				}
				ltoken = ltoken->next->next;
				delete_lexer_token(ptoken, redir_token_next);
				delete_lexer_token(ptoken, redir_token);
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
		ft_putchar_fd('\n', 1);
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
