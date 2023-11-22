
#include "minishell.h"

size_t	exist_envp(char **envp)
{
	if (!envp || !*envp)
		return (0);
	return (1);
}

void	fill_envp(t_ms *ms, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		envlst_add(&ms->envlst, envlst_new(ms, envp[i]));
		i++;
	}
}

void	update_env_content(t_ms *ms, char *env_name, char *s)
{
	t_envlst	*tmp;

	tmp = ms->envlst;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, env_name, ft_strlen(env_name) + 1) == 0)
		{
			free(tmp->content);
			tmp->content = ft_strdup(s);
		}
		tmp = tmp->next;
	}
}

void	set_default_paths(t_ms *ms)
{
	ms->user = ft_strdup(ft_getenv(ms, "USER"));
	ms->home = ft_strdup(ft_getenv(ms, "HOME"));
	ms->pwd = ft_strdup(ft_getenv(ms, "PWD"));
	ms->pwd_ppt = ft_strdup(ft_getenv(ms, "PWD"));
	update_env_content(ms, "_", "/usr/bin/env");
	update_env_content(ms, "OLDPWD", ft_getenv(ms, "PWD"));
}

t_envlst	*envlst_last(t_envlst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	envlst_add(t_envlst **lst, t_envlst *new_node)
{
	if (!new_node)
		return ;
	if (*lst != NULL)
		envlst_last(*lst)->next = new_node;
	else
		*lst = new_node;
}

t_envlst	*envlst_new(t_ms *ms, char *line)
{
	t_envlst	*node;

	node = (t_envlst *)ft_calloc(1, sizeof(t_envlst));
	if (!node)
		return (NULL);
	node->name = ft_substr(line, 0, (ft_strchr(line, '=') - line));
	node->content = ft_strdup(ft_strchr(line, '=') + 1);
	node->prev = envlst_last(ms->envlst);
	node->next = NULL;
	return (node);
}

char	*ft_getenv(t_ms *ms, char *var_name)
{
	t_envlst	*tmp;

	tmp = ms->envlst;
	while (tmp)
	{
		if (!ft_strncmp(var_name, tmp->name, ft_strlen(var_name) + 1))
			return (tmp->content);
		tmp = tmp->next;
	}
	return (NULL);
}

t_envlst	*find_env(t_ms *ms, char *env_name)
{
	t_envlst	*tmp;

	tmp = ms->envlst;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, env_name, ft_strlen(env_name) + 1) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_env(t_ms *ms)
{
	t_envlst	*tmp;

	tmp = ms->envlst;
	while (tmp)
	{
		printf("%s=%s\n", tmp->name, tmp->content);
		tmp = tmp->next;
	}
}
void	ft_unset(t_ms *ms, char *var_name)
{
	t_envlst *tmp;

	tmp = ms->envlst;
	while (tmp)
	{
		if (!ft_strncmp(var_name, tmp->name, ft_strlen(var_name) + 1))
			{
				if (tmp->prev)
					tmp->prev->next = tmp->next;
				if (tmp->next)
					tmp->next->prev = tmp->prev;
				return(free (tmp->content), free (tmp->name));
			}
		tmp = tmp->next;
	}
}

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
	}
	envlst_add(&ms->envlst, envlst_new(ms, arg));
	free (var_name);
	free (content);
}

void	ft_pwd(t_ms *ms)
{
	char	pwd[1024];

	// ms->pwd should update every time after cd or go to the next comment ;)
	if(ms->pwd)
	{
		printf("%s\n", ms->pwd);
	}
	// this is the bash original way
	else
	{
		if (getcwd(pwd, sizeof(pwd)))
			printf("%s\n", pwd);
		else
			ft_putendl_fd("ERRRRRRRROOOOOORRRR", 2);
	}
}
