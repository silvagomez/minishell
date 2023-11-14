
#include "minishell.h"

int	main(void)
{
	t_ms	ms;

	while (1)
	{
		ft_printf(MAGENTA"CONCHITA 🐚 => "RESET);
		ms.prompt = get_next_line(0);
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
				ms.prompt[ft_strlen(ms.prompt) - 1] = 0;
				create_shadow(&ms);
				tokenize_prompt(&ms);
			/* } */
		}
	}
	return (1);
}
