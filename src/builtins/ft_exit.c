
#include "minishell.h"

void	ft_exit(t_ms *ms, t_lexer_token *ltoken)
{
	if (ltoken)
		error_handling("No option required", 255);
	free_per_prompt(ms);
	free_per_instance(ms);
	ft_putendl_fd("Exit ヽ(･_･ ) (･_･)/", 1);
	//system("leaks minishell");
	exit(g_status);
}
