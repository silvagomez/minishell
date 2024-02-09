
#include "minishell.h"

void	ft_exit(t_ms *ms, t_lexer_token *ltoken)
{
	if (ltoken)
		error_handling("No option required", 255);
	free_per_prompt(ms);
	free_per_instance(ms);
	/* if (ft_strncmp("2", (find_env(ms, "SHLVL")->content), 1))
	{
		free_per_instance(ms);
		write(1, "ENTRO AL KILL\n", 15);
		kill((pid_t)(ft_atoi(ms->pid)), 0);
	} */
	//ms->exiting = 1;
	//ft_printf("G_STATUS: %i\n", g_status);
	//system("leaks minishell");
	exit(g_status);
}
