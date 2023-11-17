
#include "minishell.h"

void	set_prompt(t_ms *ms)
{
	free(ms->user);
	ms->user = ft_strdup(getenv("USER"));
	free(ms->pwd);
	ms->pwd = ft_strdup(getenv("PWD"));
	ft_printf(MAGENTA2"%s"WHITE" at "MAGENTA"CONCHITA"WHITE" in "BLUE "%s 🐚 "\
			RESET, ms->user, ms->pwd);
	ms->rline = readline("");
	if (ms->rline[0] == 0)
		printf("\n");
}
