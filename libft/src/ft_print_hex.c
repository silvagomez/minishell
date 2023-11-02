/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edejimen <edejimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:53:34 by edejimen          #+#    #+#             */
/*   Updated: 2023/11/02 12:51:42 by edejimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_hex(unsigned long nbr, int loworup)
{
	char	c;
	char	*str;
	int		count;

	count = 0;
	if (loworup == 1)
		str = ft_strdup("0123456789abcdef");
	else
		str = ft_strdup("0123456789ABCDEF");
	if (nbr >= 16)
		count += ft_print_hex(nbr / 16, loworup);
	c = str[nbr % 16];
	write(1, &c, 1);
	count++;
	free(str);
	return (count);
}
