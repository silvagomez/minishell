
#include "minishell.h"

int	main(int argc, char ** argv, char **envp)
{
	t_ms	ms;

/* 	if (!path_exists)
		return (OUT); */
	(void) argv;
	ms.envlst = NULL;
	if (argc != 1)
		return (ft_putendl_fd("Invalid arguments.", 2), -1);
	if (!exist_envp(envp))
		return (ft_putendl_fd("Env doesn't exist.", 2), -1);
	fill_envp(&ms, envp);
	set_paths(&ms);
	//printf("TEST: %s\n", getenv("var1"));
	while (1)
	{
		set_prompt(&ms);
		if (ms.rline && *(ms.rline))
			add_history(ms.rline);
		if (!ft_strncmp(ms.rline, "exit", 5))
		{
			ft_printf("exit\n");
			break ;
		}
		if (!ft_strncmp(ms.rline, "clear", 6))
			system("clear");
		else
		{
			/* if (!is_valid_quoting(&ms))
				ft_printf("COMILLAS ERRÓNEAS\n");
			else
			{ */
				//printf("rline introducido: %s", ms.rline);
				//count_pipes(&ms);
				//printf("QUOTE: %c\n%s%s\n", ms.quote, ms.rline, ms.shadow);
				//ms.rline[ft_strlen(ms.rline) - 1] = 0;
				if (!create_shadow(&ms))
					return (free_exit(&ms), 0);
				expand_test(&ms);
				tokenize_rline(&ms);
			/* } */
		}
	}
	//system("leaks minishell");
	return (1);
}
