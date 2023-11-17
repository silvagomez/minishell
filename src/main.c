
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
	//i = 0;
	fill_envp(&ms, envp);
	set_paths(&ms);
	/* while (ms.envp[i++])
	{
		if (envp[i])
			printf(GREEN"%s - "RESET, envp[i]);
		printf("%i %s\n", i, ms.envp[i]);
	}
	printf("TEST: %s\n", getenv("var1")); */
	ft_pwd(&ms);
	while (1)
	{
		/* BEFORE READLINE
		ft_printf(MAGENTA"CONCHITA 🐚 => "RESET);
		ms.rline = get_next_line(0);
		*/
		set_prompt(&ms);
		//ms.rline = readline(MAGENTA"CONCHITA 🐚 => "RESET);
		//ms.rline = readline(MAGENTA ms->prompt RESET);
		if (ms.rline)
			add_history(ms.rline);
		if (!ft_strncmp(ms.rline, "exit", 5))
		{
			ft_printf("exit\n");
			break ;
		}
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
				create_shadow(&ms);
				expand_test(&ms);
				tokenize_rline(&ms);
			/* } */
		}
	}
	return (1);
}
