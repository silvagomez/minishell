/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_uitoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edejimen <edejimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:33:37 by edejimen          #+#    #+#             */
/*   Updated: 2023/06/12 13:36:25 by edejimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_figurecount(unsigned int u)
{
	size_t	figures;
	size_t	base;
	size_t	num;

	num = (size_t)u;
	base = 10;
	figures = 1;
	while (num / base != 0)
	{
		figures++;
		base *= 10;
	}
	return ((int)figures);
}

int	ft_uitoa(unsigned int u)
{
	int		i;
	char	*str;
	int		count;

	count = 0;
	str = (char *)malloc(sizeof(char) * ft_figurecount(u) + 1);
	if (!str)
		return (0);
	str[ft_figurecount(u)] = 0;
	i = ft_figurecount(u) - 1;
	while (i >= 0)
	{
		str[i--] = (u % 10) + '0';
		u /= 10;
	}
	ft_print_str(str);
	count = ft_strlen(str);
	free(str);
	return (count);
}
