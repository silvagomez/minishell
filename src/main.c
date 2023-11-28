
#include "minishell.h"

void	free_parser_token(t_ms *ms)
{
	t_lexer_token	*ltmp;
	t_parser_token	*ptmp;

	while(ms->parser_token)
	{
		ptmp = ms->parser_token->next;
		while (ms->parser_token->lxr_list)
		{
			ltmp = ms->parser_token->lxr_list->next;
			free (ms->parser_token->lxr_list);
			ms->parser_token->lxr_list =  ltmp;
		}
		free (ms->parser_token);
		ms->parser_token = ptmp;
	}
}

int	main(int argc, char ** argv, char **envp)
{
	t_ms	ms;

	(void) argv;
	ft_memset(&ms, 0, sizeof(t_ms));
	if (argc != 1)
		return (ft_putendl_fd("Invalid arguments.", 2), -1);
	if (!exist_envp(envp))
		return (ft_putendl_fd("Env doesn't exist.", 2), -1);
	ms.envp = envp;
	fill_envp(&ms, envp);
	set_default_paths(&ms);
	dollardollar(&ms, envp);
	env_to_path(&ms, ms.envlst);
	while (1)
	{
		if(ms.parser_token)
			free_parser_token(&ms);
		set_prompt(&ms);
		if (ms.rline && *(ms.rline))
			add_history(ms.rline);
		/* if (!ft_strncmp(ms.rline, "exit", 5))
			return (printf("exit\n"), free_exit(&ms), 0); */
		if (!ft_strncmp(ms.rline, "clear", 6)) // WE CAN'T LEAVE IT THIS WAY
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
	}
	//system("leaks minishell");
	return (1);
}
