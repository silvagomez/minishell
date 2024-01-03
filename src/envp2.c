
#include "minishell.h"

size_t	size_for_array_envp(t_ms *ms)
{
	size_t		size;
	t_envlst	*tmp;

	size = 0;
	tmp = ms->envlst;
	while (tmp)
	{
		if (tmp->has_equal && tmp->scope)
			size++;
		tmp = tmp->next;
	}
	return (size);
}


void	envlist_to_array(t_ms *ms, size_t command)
{
	t_envlst	*tmp;
	int			size;
	int			idx;
	char		*str;

	tmp = ms->envlst;
	size = size_for_array_envp(ms);
	/*
	if (command == EXPORT)
		ms->envp = (char**) malloc((size + 1) * sizeof(char *));
	else if (command == UNSET)
		ms->envp = (char**) malloc((size + 2) * sizeof(char *));
	*/
	if (command == EXPORT)
		ms->envp = (char**) malloc((size + 2) * sizeof(char *));
	else if (command == UNSET)
		ms->envp = (char**) malloc((size + 1) * sizeof(char *));
	idx = 0;
	str = NULL;
	while (tmp)
	{
		if (tmp->has_equal && tmp->scope)
		{
			//printf(YEL"name = %s scope is %lu\n"RST, tmp->name, tmp->scope);
			str = ft_strjoin(tmp->name, "=");
			ms->envp[idx] = ft_strjoin(str, tmp->content);
			free(str);
			str = NULL;
			idx++;
		}
		//printf("test_new envp -----%s-------\n", ms->envp[idx]);
		tmp = tmp->next;
	}
	ms->envp[idx] = NULL;
	//printf(GRN"OK array\n");
}

