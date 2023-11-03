/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing0.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:18:32 by codespace         #+#    #+#             */
/*   Updated: 2023/11/03 16:25:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	count_pipes(t_ms *ms)
{
	char	*needle;
	size_t	i;
	size_t	j;
	int		pipe_count;

	needle = " | ";
	i = 0;
	pipe_count = 0;
	while (ms->prompt[i] && i < ft_strlen(ms->prompt))
	{
		j = 0;
		while (ms->prompt[i + j] == needle[j] && i + j < ft_strlen(ms->prompt))
		{
			if (needle[j + 1] == 0)
			{
				pipe_count++;
				i = i + j;
				break ;
			}
			j++;
		}
		i++;
	}
	ms->pipe_qty = pipe_count++;
}

void	create_shadow(t_ms *ms)
{
	int		i;
	char	quote;

	i = -1;
	quote = 0;
	ms->shadow = malloc(sizeof(char) * (ft_strlen(ms->prompt) + 1));
	ft_memset(ms->shadow, '1', ft_strlen(ms->prompt));
	while (ms->prompt[++i])
	{
		if (ms->prompt[i] == '"' || ms->prompt[i] == '\'')
		{
			quote = ms->prompt[i];
			ms->shadow[i] = '0';
			while (ms->prompt[++i] != quote)
				ms->shadow[i] = '0';
			ms->shadow[i] = '0';
		}
	}
}
