
#include "minishell.h"

/*
 * THis will be upgrade to
 */
void	ft_export(t_ms *ms, char *arg)
{
	t_envlst	*tmp;
	char		*var_name;
	char		*content;

	var_name = ft_substr(arg, 0, (ft_strchr(arg, '=') - arg));
	content = ft_strdup(ft_strchr(arg, '=') + 1);
	tmp = ms->envlst;
	while (tmp)
	{
		if (!ft_strncmp(var_name, tmp->name, ft_strlen(var_name) + 1))
		{
			free (tmp->content);
			tmp->content = content;
			free (var_name);
			return;
		}
		tmp = tmp->next;
	}

	envlst_add(&ms->envlst, envlst_new(ms, arg));
	free (var_name);
	free (content);
}
