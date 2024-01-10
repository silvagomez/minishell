
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

void	create_prompt(t_ms *ms)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(HMAG, ms->user);
	tmp2 = ft_strjoin(tmp1, HWHT);
	free (tmp1);
	tmp1 = ft_strjoin(tmp2, " at ");
	free (tmp2);
	tmp2 = ft_strjoin(tmp1, HMAG);
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, "MiniShell");
	free(tmp2);
	tmp2 = ft_strjoin(tmp1, HWHT);
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, " in ");
	free(tmp2);
	tmp2 = ft_strjoin(tmp1, CYN);
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, ms->pwd_ppt);
	free(tmp2);
	/*
	tmp2 = ft_strjoin(tmp1, RST);
	free(tmp1);
	ms->prompt = ft_strjoin(tmp2, " 🐚 ");
	free(tmp2);
	*/
	tmp2 = ft_strjoin(tmp1, RST);
	free(tmp1);
	ms->prompt = ft_strjoin(tmp2, " ");
	free(tmp2);

}

void	set_prompt(t_ms *ms)
{
	//free(ms->rline);
	free(ms->user);
	ms->user = ft_strdup(ft_getenv(ms, "USER"));
	set_pwd_prompt(ms);
	create_prompt(ms);
	/* our lovely idea until 28/DIC/2023
	ft_printf(HMAG"%s"HWHT" at "HMAG"CONCHITA"HWHT" in "CYN"%s 🐚 "\
			RST, ms->user, ms->pwd_ppt);
		ms->rline = readline("");
	*/
	ms->rline = readline(ms->prompt);
		//ms->rline = ft_strdup("");
		//exit(101);
	ft_printf("TESTEO DE RLINE: *%s*\n", ms->rline);
	if (ms->rline && ms->rline[0] == 0)
		printf("\n");
	//free (ms->pwd);
}
