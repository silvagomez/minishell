
#include "minishell.h"

void	set_prompt(t_ms *ms)
{
	ft_printf(MAGENTA2"%s"WHITE" in "MAGENTA"CONCHITA 🐚 "RESET, ms->user);
	ms->rline = readline("");
}
