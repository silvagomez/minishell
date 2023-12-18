
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
}

void	ft_cd(t_ms *ms, t_lexer_token *token)
{
	int			cd_status;
	char		*tmp_pwd;

	printf(GRN"ENTRO\n"RST);
	if (!token->next)
	{
		printf("CASE null  We need to go to HOME\n");
		cd_status = chdir(ft_getenv(ms, "HOME"));
	}
	else if (token->next->arg[0] == '/')
	{
		free (ms->pwd);
		update_env_wd(ms, "OLDPWD", ft_getenv(ms, "PWD"));
		ms->pwd = ft_strdup(token->next->arg);
		update_env_content(ms, "PWD", ms->pwd);
		cd_status = chdir(ms->pwd);
	}
	else if (!ft_strncmp("/", ms->pwd, 2) && !ft_strncmp("..", token->next->arg, 2))
		cd_status = 0;
	else if (!ft_strncmp("-", token->next->arg, 2))
	{
		printf("CASE - We need to go to OLDPWD\n");
		cd_status = chdir(ft_getenv(ms, "OLDPWD"));
	}
	else if (!ft_strncmp("..", token->next->arg, 2))
	{
		printf("CASE - We need to go to upper dir\n");
		*(ft_strrchr(ms->pwd, '/')) = 0;
		if (ft_strlen(ms->pwd) == 0)
		{
			ms->pwd[0] = '/';
			ms->pwd[1] = 0;
		}
		update_env_content(ms, "PWD", ms->pwd);
		cd_status = chdir(ft_getenv(ms, "PWD"));
	}
	else
	{
		printf("change dir to %s\n", token->next->arg);
		update_env_wd(ms, "OLDPWD", ft_getenv(ms, "PWD"));
		if (token->next->arg[ft_strlen(token->next->arg) - 1] == '/')
			token->next->arg[ft_strlen(token->next->arg) - 1] = 0;
		cd_status = chdir(token->next->arg);
		tmp_pwd = ms->pwd;
		if (!ft_strncmp("./", token->next->arg, 2))
		{
			tmp_pwd = ft_strdup(token->next->arg + 1);
			free (token->next->arg);
			token->next->arg = tmp_pwd;
		}
		else if (ft_strlen(ms->pwd) > 1)
		{
			ms->pwd = ft_strjoin(tmp_pwd, "/");
			free(tmp_pwd);
			tmp_pwd = ms->pwd;
		}
		tmp_pwd = ms->pwd;
		ms->pwd = ft_strjoin(tmp_pwd, token->next->arg);
		update_env_content(ms, "PWD", ms->pwd);
		printf("PPT: %s\n", ms->pwd);
		free (tmp_pwd);
	}
	if (cd_status != 0)
		ft_putendl_fd("Error", 2);
	printf(BLU"status %i\n", cd_status);
}
