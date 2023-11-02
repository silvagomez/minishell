/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edejimen <edejimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:33:39 by edejimen          #+#    #+#             */
/*   Updated: 2023/05/11 15:18:49 by edejimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_figurecount(int n)
{
	size_t	figures;
	size_t	base;
	size_t	num;

	num = (size_t)n;
	base = 10;
	figures = 1;
	while (n / base != 0)
	{
		figures++;
		base *= 10;
	}
	return ((int)figures);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*str;
	int		sign;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	sign = 1;
	if (n < 0)
	{
		sign = 2;
		n *= -1;
	}
	str = (char *)malloc(sizeof(char) * ft_figurecount(n) + sign);
	if (!str)
		return (NULL);
	str[(ft_figurecount(n) + sign - 1)] = 0;
	i = (ft_figurecount(n) + sign - 2);
	while (i >= sign - 1)
	{
		str[i--] = (n % 10) + '0';
		n /= 10;
	}
	if (sign == 2)
		str[0] = '-';
	return (str);
}
