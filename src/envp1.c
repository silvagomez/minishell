
#include "minishell.h"
/*
 * This function returns the size of envlst.
 */
int	envlst_node_count(t_envlst	*lst)
{
	t_envlst	*tmp;
	int			size;

	size = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	return (size);
}

/*
 * This function returns the last node of the env linked list.
 */
t_envlst	*envlst_last(t_envlst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

/*
 * This function adds a node into envlist.
 */
void	envlst_add(t_envlst **lst, t_envlst *new_node)
{
	if (!new_node)
		return ;
	if (*lst != NULL)
		envlst_last(*lst)->next = new_node;
	else
		*lst = new_node;
}

/*
 * This function creates a *node of envlist.
 */
t_envlst	*envlst_new(t_ms *ms, char *line)
{
	t_envlst	*node;

	node = (t_envlst *)ft_calloc(1, sizeof(t_envlst));
	if (!node)
		return (NULL);
	if (ft_strchr(line, '='))
	{
		node->name = ft_substr(line, 0, (ft_strchr(line, '=') - line));
		node->content = ft_strdup(ft_strchr(line, '=') + 1);
		node->has_equal = 1;
	}
	else
	{
		node->name = ft_strdup(line);
		node->content = NULL;
		node->has_equal = 0;
	}
	node->prev = envlst_last(ms->envlst);
	node->next = NULL;
	return (node);
}

void	envlist_to_array(t_ms *ms, size_t command)
{
	t_envlst	*tmp;
	int			size;
	int			idx;
	char		*str;

	tmp = ms->envlst;
	size = envlst_node_count(tmp);
	if (command == EXPORT)
		ms->envp = (char**) malloc((size + 1) * sizeof(char *));
	else if (command == UNSET)
		ms->envp = (char**) malloc((size + 2) * sizeof(char *));
	idx = 0;
	str = NULL;
	while (tmp)
	{
		if (tmp->has_equal)
		{
			str = ft_strjoin(tmp->name, "=");
			ms->envp[idx] = ft_strjoin(str, tmp->content);
		}
		else
		{
			ms->envp[idx] = ft_strdup(tmp->name);
		}
		//printf("test_new envp -----%s-------\n", ms->envp[idx]);
		free(str);
		str = NULL;
		tmp = tmp->next;
		idx++;
	}
	ms->envp[idx] = NULL;
	//printf(GRN"OK array\n");
}

