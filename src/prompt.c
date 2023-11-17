
#include "minishell.h"

/*
 * cd will update PWD
 */
void	set_pwd_prompt(t_ms *ms)
{
	size_t i;

	if (ms->pwd_ppt)
	{
		if (ft_strncmp(ms->pwd, ms->home, ft_strlen(ms->home)) == 0)
		{
			printf("PWD CONTIENE HOME \n%s\n%s\n", ms->pwd, ms->home);
			i = ft_strlen(ms->home);
			ms->pwd_ppt = ft_strjoin("~", ms->pwd + i);
		}
		else
		{
			free(ms->pwd_ppt);
			ms->pwd_ppt = ft_strdup(ft_getenv(ms, "PWD"));
		}
	}
	else
		ms->pwd_ppt = ft_strdup(ft_getenv(ms, "PWD"));
}

void	set_prompt(t_ms *ms)
{
	free(ms->user);
	ms->user = ft_strdup(ft_getenv(ms, "USER"));
	set_pwd_prompt(ms);
	ft_printf(MAGENTA2"%s"WHITE" at "MAGENTA"CONCHITA"WHITE" in "BLUE "%s 🐚 "\
			RESET, ms->user, ms->pwd_ppt);
	ms->rline = readline("");
	if (ms->rline[0] == 0)
		printf("\n");
}
