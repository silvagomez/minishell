/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edejimen <edejimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:56:13 by edejimen          #+#    #+#             */
/*   Updated: 2023/06/12 13:34:55 by edejimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_ptr(unsigned long ptr)
{
	int	count;

	write (1, "0x", 2);
	count = 2;
	count += ft_print_hex(ptr, 1);
	return (count);
}
