/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 12:18:32 by codespace         #+#    #+#             */
/*   Updated: 2023/11/03 12:36:07 by codespace        ###   ########.fr       */
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
