/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edejimen <edejimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:57:53 by edejimen          #+#    #+#             */
/*   Updated: 2023/06/12 13:34:59 by edejimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_str(char *str)
{
	int	i;
	int	count;

	if (!str)
		str = "(null)";
	i = 0;
	count = 0;
	while (str[i])
	{
		write (1, &str[i], 1);
		i++;
		count++;
	}
	return (count);
}
