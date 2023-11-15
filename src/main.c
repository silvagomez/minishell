
#include "minishell.h"

void	fill_envp(t_ms *ms, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
		i++;
	ms->envp = (char **) malloc (sizeof(char *) * i + 1);
	i = 0;
	while (envp[i])
		{
			ms->envp[i] = ft_strdup(envp[i]);
			i++;
		}
	ms->envp[i] = 0;
}

size_t	exist_envp(char **envp)
{
	if (!envp || !*envp)
		return (0);
	return (1);
}

int	main(int argc, char ** argv, char **envp)
{
	t_ms	ms;
	//int i;

/* 	if (!path_exists)
		return (OUT); */
	(void) argv;
	if (argc != 1)
		return (ft_putendl_fd("Invalid arguments.", 2), -1);
	if (!exist_envp(envp))
		return (ft_putendl_fd("Env doesn't exist.", 2), -1);
	//i = 0;
	fill_envp(&ms, envp);
	/* while (ms.envp[i++])
	{
		if (envp[i])
			printf(GREEN"%s - "RESET, envp[i]);
		printf("%i %s\n", i, ms.envp[i]);
	}
	printf("TEST: %s\n", getenv("var1")); */
	while (1)
	{
		/* BEFORE READLINE
		ft_printf(MAGENTA"CONCHITA 🐚 => "RESET);
		ms.prompt = get_next_line(0);
		*/
		ms.prompt = readline(MAGENTA"CONCHITA 🐚 => "RESET);
		if (ms.prompt)
			add_history(ms.prompt);
		if (!ft_strncmp(ms.prompt, "exit", 4))
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
				//printf("Prompt introducido: %s", ms.prompt);
				//count_pipes(&ms);
				//printf("QUOTE: %c\n%s%s\n", ms.quote, ms.prompt, ms.shadow);
				//ms.prompt[ft_strlen(ms.prompt) - 1] = 0;
				create_shadow(&ms);
				expand_test(&ms);
				tokenize_prompt(&ms);
			/* } */
		}
	}
	return (1);
}
