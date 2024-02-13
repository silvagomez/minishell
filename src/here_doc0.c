
#include "minishell.h"

t_hdlst	*hdlst_last(t_hdlst *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	hdlst_add(t_hdlst **lst, t_hdlst *new_node)
{
	if (!new_node)
		return ;
	if (*lst != NULL)
		hdlst_last(*lst)->next = new_node;
	else
		*lst = new_node;
}

int	hdlst_count(t_hdlst *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

t_hdlst	*hdlst_new(char *str)
{
	t_hdlst	*node;

	node = (t_hdlst *)ft_calloc(1, sizeof(t_hdlst));
	if (!node)
		return (NULL);
	node->str = ft_strdup(str);
	node->next = NULL;
	return (node);
}

void	hdlst_delete(t_parser_token *ptoken, t_hdlst *node)
{
	ptoken->hd_list = node->next;
	free (node->str);
	free(node);
}

void	manage_heredoc(t_parser_token *ptoken)
{
	pid_t	id;

	if (!ptoken->hd_str)
		ptoken->hd_str = ft_strdup("");
	if (pipe(ptoken->hd_pipe) != 0)
		error_handling("Pipe fail", EXIT_FAILURE);
	set_signal_action(SIGHD);
	id = fork();
	if (!id)
		hd_child(ptoken);
	else
		hd_father(ptoken, id);
	set_signal_action(SIGEXE);
}

void	hd_child(t_parser_token *ptoken)
{
	size_t		len;
	int			cmp;
	char		*tmp;

	while (1)
	{
		len = ft_strlen(ptoken->hd_list->str);
		free (ptoken->hd_line);
		ptoken->hd_line = get_next_line(0);
		if (ptoken->hd_line)
		{
			cmp = ft_strncmp(ptoken->hd_list->str, ptoken->hd_line, len);
			if (len + 1 == ft_strlen(ptoken->hd_line) && !cmp)
			{
				hdlst_delete(ptoken, ptoken->hd_list);
				free (ptoken->hd_line);
				ptoken->hd_line = ft_strdup("");
			}
			if (!ptoken->hd_list)
				break ;
			if (hdlst_count(ptoken->hd_list) == 1)
			{
				tmp = ptoken->hd_str;
				ptoken->hd_str = ft_strjoin(ptoken->hd_str, ptoken->hd_line);
				free (tmp);
			}
		}
		else if (hdlst_count(ptoken->hd_list) == 1)
			break ;
		else
			hdlst_delete(ptoken, ptoken->hd_list);
	}
	close(ptoken->hd_pipe[0]);
	/* if (ft_strlen(ptoken->hd_str) > 0)
		ptoken->hd_str[ft_strlen(ptoken->hd_str) - 1] = 0; */
	//ft_printf("EL HEREDOC CONTIENE: *%s*\n", ptoken->hd_str);
	ft_putstr_fd(ptoken->hd_str, ptoken->hd_pipe[1]);
	close(ptoken->hd_pipe[1]);
	exit(0);
}

void	hd_father(t_parser_token *ptoken, pid_t id)
{
	int	status;

	close(ptoken->hd_pipe[1]);
	waitpid(id, &status, 0);
}
