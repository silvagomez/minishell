/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:47:12 by codespace         #+#    #+#             */
/*   Updated: 2023/11/02 16:22:47 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	int		control;
	char	*buff;

	control = 0;
	buff = ft_strdup("");
	while (1)
	{
		if (control == 0)
		{
			ft_printf("CONCHITA 🐚 => ");
			g_ms.prompt = get_next_line(0);
			if (!ft_strncmp(g_ms.prompt, "exit", 4))
				break ;
			if (!control && ft_strchr(g_ms.prompt, '"') && ft_strchr(g_ms.prompt, '"') == ft_strrchr(g_ms.prompt, '"'))
				control = 1;
			else
			{
				printf("Prompt introducido: %s", g_ms.prompt);
				add_history(g_ms.prompt);
				free(g_ms.prompt);
			}
		}
		else //CONTROL == 1
		{
			write(1, ">", 1);
			buff = ft_strjoin(buff, g_ms.prompt);
			g_ms.prompt = get_next_line(0);
			if (ft_strchr(g_ms.prompt, '"'))
			{
				control = 0;
				ft_printf("%s", buff + 1);
			}
		}
	}
	return (1);
}
