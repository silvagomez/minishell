/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:47:12 by codespace         #+#    #+#             */
/*   Updated: 2023/11/02 12:16:53 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	ft_printf("MINICONCHA 🐚 => ");
	g_ms.prompt = get_next_line(0);
	if (strncmp(g_ms.prompt, "exit", 4))
		printf("Prompt introducido: \"%s\"", g_ms.prompt);
	else
		return (1);
	return (1);
}
