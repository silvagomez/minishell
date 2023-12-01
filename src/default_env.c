
#include "minishell.h"

/*
 * This function fills data to *ms varaibles and set a deault env variables when
 * a shell is launching in this case *envlist.
 */
void	set_default_paths(t_ms *ms)
{
	int	fd;

	ms->user = ft_strdup(ft_getenv(ms, "USER"));
	ms->home = ft_strdup(ft_getenv(ms, "HOME"));
	ms->pwd = ft_strdup(ft_getenv(ms, "PWD"));
	ms->pwd_ppt = ft_strdup(ft_getenv(ms, "PWD"));
	update_env_content(ms, "_", "/usr/bin/env");
	update_env_content(ms, "OLDPWD", ft_getenv(ms, "PWD"));
	fd = open("os_name", O_RDONLY);
	ms->os_name = get_next_line(fd);
	if (ms->os_name)
		*ft_strchr(ms->os_name, '\n') = 0;
	close (fd);
	printf("OS NAME: %s\n", ms->os_name);
	unlink("os_name");
}
