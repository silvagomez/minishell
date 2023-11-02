/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:47:12 by codespace         #+#    #+#             */
/*   Updated: 2023/11/02 13:10:13 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(void)
{
	while (1)
	{
		ft_printf("MINICONCHA 🐚 => ");
		g_ms.prompt = get_next_line(0);
		if (strncmp(g_ms.prompt, "exit", 4))
		{
			//write(1, "Prompt introducido: ", 21);
			//write(1, g_ms.prompt, ft_strlen(g_ms.prompt));
			//write(1, "\"", 1);
			printf("Prompt introducido: %s", g_ms.prompt);
			//fflush(stdout);
			free (g_ms.prompt);
		}
		else
			break ;
	}
	return (1);
}
