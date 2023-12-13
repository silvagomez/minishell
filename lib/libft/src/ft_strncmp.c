/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edejimen <edejimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 16:41:26 by edejimen          #+#    #+#             */
/*   Updated: 2023/05/11 15:29:02 by edejimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	c;
	int				d;

	c = 0;
	d = 0;
	while ((c < n) && !d && (s1[c] != '\0') && (s2[c] != '\0'))
	{
		d = (unsigned char)s1[c] - (unsigned char)s2[c];
		c++;
	}
	if (c < n && !d && (s1[c] == '\0' || s2[c] == '\0'))
		d = (unsigned char)s1[c] - (unsigned char)s2[c];
	return (d);
}
