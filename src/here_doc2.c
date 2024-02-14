
#include "minishell.h"

void	manage_heredoc(t_parser_token *ptoken)
{
	pid_t	id;

	if (!ptoken->hd_str)
		ptoken->hd_str = ft_strdup("");
	if (pipe(ptoken->hd_pipe) != 0)
		error_handling("Pipe fail", EXIT_FAILURE);
	set_signal_action(SIGHD);
	id = fork();
	if (!id)
		hd_child(ptoken);
	else
		hd_father(ptoken, id);
	set_signal_action(SIGEXE);
}
