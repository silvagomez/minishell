
#include "minishell.h"

void	set_default_paths(t_ms *ms)
{
	ms->user = ft_strdup(ft_getenv(ms, "USER"));
	ms->home = ft_strdup(ft_getenv(ms, "HOME"));
	ms->pwd = ft_strdup(ft_getenv(ms, "PWD"));
	ms->pwd_ppt = ft_strdup(ft_getenv(ms, "PWD"));
	update_env_content(ms, "_", "/usr/bin/env");
	update_env_content(ms, "OLDPWD", ft_getenv(ms, "PWD"));
}
