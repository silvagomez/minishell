
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

size_t	is_dir(char *dir_name)
{
	DIR	*dirp;

	dirp = opendir(dir_name);
	if (dirp)
	{
		closedir(dirp);
		return (1);
	}
	return (0);
}

void	ft_cd(t_ms *ms, t_lexer_token *ltoken)
{
	int			cd_status;
	char		*tmp_pwd;

	printf(GRN"ENTRO\n"RST);
	if (ft_getenv(ms, "PWD") == NULL)
	{
		ft_export(ms, "PWD=Init", 1);
		free (ms->pwd);
		ms->pwd = ft_strdup(get_pwd());
		update_env_wd(ms, "PWD", ms->pwd);
	}
	if (!ltoken->next)
	{
		if (ft_getenv(ms, "HOME"))
		{
			cd_status = chdir(ft_getenv(ms, "HOME"));
			if (ft_getenv(ms, "OLDPWD"))
				update_env_wd(ms, "OLDPWD", ft_getenv(ms, "PWD"));
			else
			{
				ft_export(ms, "OLDPWD=Init", 1);
				update_env_wd(ms, "OLDPWD", ft_getenv(ms, "PWD"));
			}
			update_env_wd(ms, "PWD", ft_getenv(ms, "HOME"));
			free(ms->pwd);
			ms->pwd = ft_strdup(ft_getenv(ms, "HOME"));
			//ms->pwd = get_pwd();
		}
		else
		{
			ft_putendl_fd("bash: cd: HOME not set", 2);
			cd_status = 1;
		}
	}
	else if (!ft_strncmp("-", ltoken->next->arg, 2))
	{
		printf(GRN"ENTRO (-)\n"RST);
		if (ft_getenv(ms, "OLDPWD"))
		{
			cd_status = chdir(ft_getenv(ms, "OLDPWD"));
			tmp_pwd = ft_strdup(ft_getenv(ms, "OLDPWD"));
			update_env_wd(ms, "OLDPWD", ft_getenv(ms, "PWD"));
			update_env_wd(ms, "PWD", tmp_pwd);
			free(tmp_pwd);
			free (ms->pwd);
			ms->pwd = ft_strdup(get_pwd());
		}
		else
		{
			ft_putendl_fd("bash: cd: OLDPWD not set", 2);
			cd_status = 1;
		}
	}
	else
	{
		printf(GRN"ENTRO (else)\n"RST);
		if (access(ltoken->next->arg, F_OK) == 0 && is_dir(ltoken->next->arg))
		{
		printf(GRN"ENTRO (else2)\n"RST);
			cd_status = chdir(ltoken->next->arg);
			if (cd_status == 0)
			{
				if (ft_getenv(ms, "OLDPWD"))
					update_env_wd(ms, "OLDPWD", ft_getenv(ms, "PWD"));
				else
				{
					ft_export(ms, "OLDPWD=Init", 1);
					update_env_wd(ms, "OLDPWD", ft_getenv(ms, "PWD"));
				}
				update_env_wd(ms, "PWD", ltoken->next->arg);
				free(ms->pwd);
				ms->pwd = ft_strdup(get_pwd());
				//update_env_content(ms, );
			}
			else
				ft_printf("bash: cd: %s: No such file or directory\n", ltoken->next->arg);
		}
		else
		{
			ft_printf("bash: cd: %s: No such file or directory\n", ltoken->next->arg);
			cd_status = 1;
		}

	}
	/*
	else if (ltoken->next->arg[0] == '/')
	{
		// access F_OK?
		cd_status = chdir(ltoken->next->arg);
		//check if cd_status ok should update env
		free (ms->pwd);
		ms->pwd = ft_strdup(ltoken->next->arg);
		update_env_wd(ms, "OLDPWD", ft_getenv(ms, "PWD"));
		update_env_wd(ms, "PWD", ltoken->next->arg);
	}
	else if (!ft_strncmp("..", ltoken->next->arg, 2))
	{
		printf("CASE - We need to go to upper dir\n");
		cd_status = chdir(ltoken->next->arg);
	}
	else
	{
		printf("change dir to %s\n", ltoken->next->arg);
		update_env_wd(ms, "OLDPWD", ft_getenv(ms, "PWD"));
		if (ltoken->next->arg[ft_strlen(ltoken->next->arg) - 1] == '/')
			ltoken->next->arg[ft_strlen(ltoken->next->arg) - 1] = 0;
		cd_status = chdir(ltoken->next->arg);
		tmp_pwd = ms->pwd;
		if (!ft_strncmp("./", ltoken->next->arg, 2))
		{
			tmp_pwd = ft_strdup(ltoken->next->arg + 1);
			free (ltoken->next->arg);
			ltoken->next->arg = tmp_pwd;
		}
		else if (ft_strlen(ms->pwd) > 1)
		{
			ms->pwd = ft_strjoin(tmp_pwd, "/");
			free(tmp_pwd);
			tmp_pwd = ms->pwd;
		}
		tmp_pwd = ms->pwd;
		ms->pwd = ft_strjoin(tmp_pwd, ltoken->next->arg);
		update_env_content(ms, "PWD", ms->pwd);
		printf("PPT: %s\n", ms->pwd);
		free (tmp_pwd);
	}
	*/
	if (cd_status != 0)
		ft_putendl_fd("Error", 2);
	printf(BLU"status %i\n", cd_status);
}
