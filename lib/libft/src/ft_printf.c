/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edejimen <edejimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 13:52:28 by edejimen          #+#    #+#             */
/*   Updated: 2023/06/12 13:35:04 by edejimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_check_type(char c, va_list args)
{
	int		count;

	count = 0;
	if (c == 's')
		count += ft_print_str(va_arg(args, char *));
	if (c == 'c')
		count += ft_print_char(va_arg(args, unsigned int));
	if (c == 'i' || c == 'd')
		count += ft_print_num(va_arg(args, int));
	if (c == '%')
		count += ft_print_char('%');
	if (c == 'u')
		count += ft_uitoa(va_arg(args, unsigned int));
	if (c == 'x')
		count += ft_print_hex(va_arg(args, unsigned int), 1);
	if (c == 'X')
		count += ft_print_hex(va_arg(args, unsigned int), 2);
	if (c == 'p')
		count += ft_print_ptr((unsigned long)va_arg(args, void *));
	return (count);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	int		count;
	int		i;

	i = 0;
	count = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] != '%')
		{
			ft_print_char(str[i]);
			count++;
			i++;
		}
		else
		{
			i++;
			count += ft_check_type(str[i++], args);
		}
	}
	va_end(args);
	return (count);
}
