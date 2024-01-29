
#include "minishell.h"

sig_atomic_t	g_status;

int	main(int argc, char **argv, char **envp)
{
	t_ms	ms;

	(void) argv;
	ft_memset(&ms, 0, sizeof(t_ms));
	if (argc != 1)
		error_handling(ERR_IARG, 1);
	if (!exist_envp(envp))
		error_handling(ERR_ENVK, 1);
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
		if (ms.rline && !ft_strncmp(ms.rline, "clear", 6)) // WE CAN'T LEAVE IT THIS WAY
			system("clear");
		else
		{
			if (!create_shadow(&ms))
				return (free_exit(&ms), 0);
			expand_test(&ms);
			tokenize_rline(&ms);
			if (ms.lexer_token)
				tokenize_parser(&ms);
		}
		free_per_prompt(&ms);
	}
	//system("leaks minishell");
	return (0);
}
