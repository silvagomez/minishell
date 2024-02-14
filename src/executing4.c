
#include "minishell.h"

void	check_ptoken_heredoc(t_parser_token *ptoken)
{
	if (ptoken->is_here_doc)
	{
		ptoken->input_fd = dup(ptoken->hd_pipe[0]);
		close (ptoken->hd_pipe[0]);
	}
}

void	check_ptoken_input_heredoc(t_parser_token *ptoken)
{
	if (ptoken->is_input || ptoken->is_here_doc)
	{
		dup2(ptoken->input_fd, STDIN_FILENO);
		close (ptoken->input_fd);
	}
}

void	check_ptoken_output_fd(t_parser_token *ptoken)
{
	if (ptoken->output_fd > 2)
	{
		dup2(ptoken->output_fd, STDOUT_FILENO);
		close (ptoken->output_fd);
	}
}
