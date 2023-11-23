
#include "minishell.h"

void	update_env_wd(t_ms *ms, char *env_name, char *arg)
{
	t_envlst	*tmp;	
	char		*str;

	tmp = find_env(ms, env_name);
	if (!tmp)
	{
		str = ft_strjoin(env_name, "=");
		arg = ft_strjoin(str, arg);
		envlst_add(&ms->envlst, envlst_new(ms, arg));
		free(str);
	}
	else
		update_env_content(ms, env_name, arg);
	//Consider freeing in some of the cases!!
	//free(arg);
}

void	ft_cd(t_ms *ms)
{
	int			cd_status;
	//char		pwd[1024];

	printf(GRN"ENTRO\n"RST);
	if (!ms->lexer_token->next)
	{
		printf("CASE null  We need to go to HOME\n");
		cd_status = chdir(ft_getenv(ms, "HOME"));
		//return ;
	}
	else if (*(ms->lexer_token->next->arg) == '-')
	{
		printf("CASE - We need to go to OLDPWD\n");
		cd_status = chdir(ft_getenv(ms, "OLDPWD"));
		//return ;
	}
	else
	{
		printf("change dir to %s\n", ms->lexer_token->next->arg);
		update_env_wd(ms, "OLDPWD", ft_getenv(ms, "OLDPWD"));
		cd_status = chdir(ms->lexer_token->next->arg);
		//return ;
	}
	if (cd_status != 0)
		ft_putendl_fd("Error", 2);
	printf(BLU"status %i\n", cd_status);
}
