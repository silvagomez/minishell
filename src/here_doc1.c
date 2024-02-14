
#include "minishell.h"

void	hd_child_part1(t_parser_token *ptoken, size_t	*len)
{
		*len = ft_strlen(ptoken->hd_list->str);
		free (ptoken->hd_line);
		ptoken->hd_line = get_next_line(0);
}
void	hd_child_part2(t_parser_token *ptoken, size_t	*len)
{
	int			cmp;

	cmp = ft_strncmp(ptoken->hd_list->str, ptoken->hd_line, *len);
	if ((*len) + 1 == ft_strlen(ptoken->hd_line) && !cmp)
	{
		hdlst_delete(ptoken, ptoken->hd_list);
		free (ptoken->hd_line);
		ptoken->hd_line = ft_strdup("");
	}
}

void	hd_child_part3(t_parser_token *ptoken)
{
	char		*tmp;

	if (hdlst_count(ptoken->hd_list) == 1)
	{
		tmp = ptoken->hd_str;
		ptoken->hd_str = ft_strjoin(ptoken->hd_str, ptoken->hd_line);
		free (tmp);
	}
}

void	hd_child(t_parser_token *ptoken)
{
	size_t		len;

	while (1)
	{
		hd_child_part1(ptoken, &len);
		if (ptoken->hd_line)
		{
			hd_child_part2(ptoken, &len);
			if (!ptoken->hd_list)
				break ;
			hd_child_part3(ptoken);
		}
		else if (hdlst_count(ptoken->hd_list) == 1)
			break ;
		else
			hdlst_delete(ptoken, ptoken->hd_list);
	}
	close(ptoken->hd_pipe[0]);
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
