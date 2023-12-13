/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edejimen <edejimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 13:38:46 by edejimen          #+#    #+#             */
/*   Updated: 2023/05/11 16:07:42 by edejimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	slen;
	size_t	sublen;

	if (!s)
		return (0);
	slen = ft_strlen((char *)s);
	if (!s[0] || slen <= start)
		return (ft_strdup(""));
	if (len > slen - start)
		sublen = slen - start;
	else
		sublen = len;
	sub = malloc((sublen + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (s[start + i] && i < len)
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[i] = 0;
	return (sub);
}
