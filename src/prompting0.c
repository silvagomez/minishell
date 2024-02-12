
#include "minishell.h"

/*
 * cd will update PWD
 */
void	set_pwd_prompt(t_ms *ms)
{
	size_t	i;

	if (ft_strncmp(ms->pwd, ms->home, ft_strlen(ms->home)) == 0)
	{
		i = ft_strlen(ms->home);
		free(ms->pwd_ppt);
		ms->pwd_ppt = ft_strjoin("~", ms->pwd + i);
	}
	else
	{
		free(ms->pwd_ppt);
		ms->pwd_ppt = ft_strdup(ft_getenv(ms, "PWD"));
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
	tmp2 = ft_strjoin(tmp1, RST);
	free(tmp1);
	ms->prompt = ft_strjoin(tmp2, " ");
	free(tmp2);

}

void	set_prompt(t_ms *ms)
{
	free(ms->user);
	ms->user = ft_strdup(ft_getenv(ms, "USER"));
	set_pwd_prompt(ms);
	create_prompt(ms);
	ms->rline = readline(ms->prompt);
	if (ms->rline == NULL)
	{
		//free all!!!!
		free_per_prompt(ms);
		free_per_instance(ms);
		ft_putendl_fd("Exit ヽ(･_･ ) (･_･)/", 1);
		//system("leaks minishell");
		exit(0);
	}
	ft_printf("TESTEO DE RLINE: *%s*\n", ms->rline);
	if (ms->rline && ms->rline[0] == 0)
		printf("\n");
}
