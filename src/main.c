
#include "minishell.h"

sig_atomic_t	g_status;

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	(void) argv;
	eee = envp;
	ft_memset(&ms, 0, sizeof(t_ms));
	if (argc != 1)
		error_handling_exit(ERR_IARG, EXIT_FAILURE);
	if (!exist_envp(envp))
		error_handling_exit(ERR_ENVK, EXIT_FAILURE);
	fill_envp(&ms, envp);
	set_default_paths(&ms, envp);
	dollardollar(&ms, envp);
	env_to_path(&ms, ms.envlst);
	while (1)
	{
		//set_signal_action(SIGDEF);
		set_prompt(&ms);
		if (ms.rline && *(ms.rline))
			add_history(ms.rline);
		if (ms.rline && !ft_strncmp(ms.rline, "clear", 6))
			ft_clear(envp);
		else
		{
			if (!create_shadow(&ms))
				error_handling(ERR_UNQT, EXIT_FAILURE);
			else
			{
				expanding(&ms);
				tokenize_rline(&ms);
				if (ms.lexer_token)
					tokenize_parser(&ms);
			}
		}
		free_per_prompt(&ms);
	}
	//system("leaks minishell");
	//this return must be deleted, we can only get out from minishell through 
	//signal or exit;
	return (0);
}
