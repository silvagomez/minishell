
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

void	check_redir_output(t_parser_token *ptoken) //redir = 3 '>'
{
	t_lexer_token	*ltoken;
	t_lexer_token	*redir_token;
	t_lexer_token	*redir_token_next;


	ltoken = ptoken->lxr_list;
	while (ltoken)
	{
		if (ltoken->tag_redir == 3)
			{
				redir_token = ltoken;
				redir_token_next = ltoken->next;
				if (!ltoken->next)
				{
					printf(HRED"INVALID PROMPT"RST"\n");
					exit(1);
				}
				else
				{
					if (ptoken->output_fd != 1)
						close(ptoken->output_fd);
					ptoken->output_fd = open (ltoken->next->arg, O_TRUNC | O_RDWR | O_CREAT, 0777);
					if(ptoken->output_fd == -1)
						ft_putendl_fd("Permission denied", 2);
				}
				ltoken = ltoken->next->next;
				delete_lexer_token(ptoken, redir_token);
				/* free (redir_token->arg);
				free (redir_token); */
				delete_lexer_token(ptoken, redir_token_next);
				/* free (redir_token_next->arg);
				free (redir_token_next); */
			}
		else
			ltoken = ltoken->next;
	}
}

void	check_redirs(t_parser_token *ptoken)
{
	check_redir_output(ptoken);
	//check_redir_input();
	//check_redir_append();
	//check_redir_here_doc();
}
