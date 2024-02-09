
#include "minishell.h"

void	ft_exit(t_ms *ms, t_lexer_token *ltoken)
{
	if (ltoken)
		error_handling("No option required", 255);
	free_per_prompt(ms);
	free_per_instance(ms);
	system("leaks minishell");
	exit(g_status);
}
