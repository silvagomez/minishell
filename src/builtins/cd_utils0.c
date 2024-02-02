
#include "minishell.h"

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

int	ch_back_forward(t_ms *ms)
{
	int		status;
	char	*tmp_pwd;

	if (ft_getenv(ms, "OLDPWD"))
	{
		status = chdir(ft_getenv(ms, "OLDPWD"));
		if (status == 0)
		{
			tmp_pwd = ft_strdup(ft_getenv(ms, "OLDPWD"));
			update_env_wd(ms, "OLDPWD", ft_getenv(ms, "PWD"));
			update_env_wd(ms, "PWD", tmp_pwd);
			free(tmp_pwd);
			free (ms->pwd);
			ms->pwd = ft_strdup(get_pwd());
		}
		else
			error_handling(ERR_CDER, EXIT_FAILURE);
	}
	else
	{
		error_handling(ERR_CDOP, EXIT_FAILURE);
		status = 1;
	}
	return (status);
}

void	ch_directory(t_ms *ms, int status)
{
	if (status == 0)
	{
		if (ft_getenv(ms, "OLDPWD"))
			update_env_wd(ms, "OLDPWD", ft_getenv(ms, "PWD"));
		else
		{
			ft_export(ms, "OLDPWD=Init", 0);
			update_env_wd(ms, "OLDPWD", ft_getenv(ms, "PWD"));
		}
		update_env_wd(ms, "PWD", get_pwd());
		free(ms->pwd);
		ms->pwd = ft_strdup(get_pwd());
	}
	else
		error_handling(ERR_CDER, EXIT_FAILURE);
}
