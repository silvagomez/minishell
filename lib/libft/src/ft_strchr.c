/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edejimen <edejimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 11:48:13 by edejimen          #+#    #+#             */
/*   Updated: 2023/05/11 15:26:53 by edejimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)s;
	while (str[i] != 0)
	{
		if (str[i] == (unsigned char)c)
			return (&str[i]);
		else
			i++;
	}
	if ((unsigned char)c == 0)
		return (&str[i]);
	return (NULL);
}
