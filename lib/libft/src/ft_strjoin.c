/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edejimen <edejimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 14:45:59 by edejimen          #+#    #+#             */
/*   Updated: 2023/05/11 15:27:34 by edejimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*s3;
	char	*str1;
	char	*str2;

	str1 = (char *)s1;
	str2 = (char *)s2;
	s3 = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!s3)
		return (NULL);
	i = 0;
	while (s1[i] != 0)
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[i - ft_strlen((char *)s1)] != 0)
	{
		s3[i] = s2[i - ft_strlen((char *)s1)];
		i++;
	}
	s3[i] = 0;
	return (s3);
}
