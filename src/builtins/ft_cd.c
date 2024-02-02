
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

void	update_home_pwd_oldpwd(t_ms *ms)
{
	if (ft_getenv(ms, "OLDPWD"))
		update_env_wd(ms, "OLDPWD", ft_getenv(ms, "PWD"));
	else
	{
		ft_export(ms, "OLDPWD=Init", 0);
		update_env_wd(ms, "OLDPWD", ft_getenv(ms, "PWD"));
	}
	update_env_wd(ms, "PWD", ft_getenv(ms, "HOME"));
	free(ms->pwd);
	ms->pwd = ft_strdup(ft_getenv(ms, "HOME"));
	//ms->pwd = get_pwd();
}

int	ch_home(t_ms *ms)
{
	int	status;

	if (ft_getenv(ms, "HOME"))
	{
		status = chdir(ft_getenv(ms, "HOME"));
		if (status == 0)
			update_home_pwd_oldpwd(ms);
		else
			error_handling(ERR_CDER, EXIT_FAILURE);
	}
	else
	{
		error_handling(ERR_CDHM, EXIT_FAILURE);
		status = 1;
	}
	return (status);
}

void	init_pwd(t_ms *ms)
{
	ft_export(ms, "PWD=Init", 0);
	free (ms->pwd);
	ms->pwd = ft_strdup(get_pwd());
	update_env_wd(ms, "PWD", ms->pwd);
}

int	ft_cd(t_ms *ms, t_lexer_token *ltoken)
{
	int			status;

	if (ft_getenv(ms, "PWD") == NULL)
		init_pwd(ms);
	if (!ltoken->next)
		status = ch_home(ms);
	else if (!ft_strncmp("~", ltoken->next->arg, 2))
		status = ch_home(ms);
	else if (!ft_strncmp("-", ltoken->next->arg, 2))
		status = ch_back_forward(ms);
	else
	{
		if (access(ltoken->next->arg, F_OK) == 0 && is_dir(ltoken->next->arg))
		{
			status = chdir(ltoken->next->arg);
			ch_directory(ms, status);
		}
		else
		{
			error_handling(ERR_CDER, EXIT_FAILURE);
			status = 1;
		}
	}
	return (status);
}
