
#include "minishell.h"

void	display_sort_env(t_ms *ms)
{
	t_envlist	*temp1;

	memset();

}


void	set_order_envlst(t_ms *ms)
{
	int	id;
	
}

/*
 * This will be upgraded to
 */
void	ft_export(t_ms *ms, char *arg)
{
	t_envlst	*tmp;
	char		*var_name;
	char		*content;

	set_order_envlst(ms);
	if (!arg)
		display_sort_env(ms);
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
