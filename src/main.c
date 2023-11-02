/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:47:12 by codespace         #+#    #+#             */
/*   Updated: 2023/11/02 22:45:55 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_ms	ms;

	while (1)
	{
		ft_printf("CONCHITA 🐚 => ");
		ms.prompt = get_next_line(0);
		if (!ft_strncmp(ms.prompt, "exit", 4))
		{
			ft_printf("exit\n");
			break ;
		}
		else
		{
			if (!is_valid_quoting(&ms))
				ft_printf("COMILLAS ERRÓNEAS\n");
			else
			{
				printf("Prompt introducido: %s", ms.prompt);
				add_history(ms.prompt);
				free(ms.prompt);
			}
		}
	}
	return (1);
}
