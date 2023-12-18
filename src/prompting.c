
#include "minishell.h"

/*
 * cd will update PWD
 */
void	set_pwd_prompt(t_ms *ms)
{
	size_t	i;
	//char	pwd[1024];

	//update_env_wd(ms, "PWD", ft_getenv(ms, "OLDPWD"));
	//free(ms->pwd);
	//ms->pwd = ft_strdup(ft_getenv(ms, "PWD"));
	if (ft_strncmp(ms->pwd, ms->home, ft_strlen(ms->home)) == 0)
	{
		//printf("PWD CONTIENE HOME \n%s\n%s\n", ms->pwd, ms->home);
		i = ft_strlen(ms->home);
		free(ms->pwd_ppt);
		ms->pwd_ppt = ft_strjoin("~", ms->pwd + i);
		//printf(HRED"HELLO1? %s\n"RST, ms->pwd_ppt);
	}
	else
	{
		free(ms->pwd_ppt);
		ms->pwd_ppt = ft_strdup(ft_getenv(ms, "PWD"));
		//printf(HRED"HELLO2? %s\n"RST, ms->pwd_ppt);
	}
}

void	set_prompt(t_ms *ms)
{
	//free(ms->rline);
	free(ms->user);
	ms->user = ft_strdup(ft_getenv(ms, "USER"));
	set_pwd_prompt(ms);
	ft_printf(HMAG"%s"HWHT" at "HMAG"CONCHITA"HWHT" in "CYN"%s 🐚 "\
			RST, ms->user, ms->pwd_ppt);
	ms->rline = readline("");
	if (ms->rline == NULL)
		ft_putendl_fd("hola", 1);
		//exit(101);
	if (ms->rline && ms->rline[0] == 0)
		printf("\n");
	//free (ms->pwd);
}
