/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edejimen <edejimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:38:26 by edejimen          #+#    #+#             */
/*   Updated: 2023/05/11 15:18:21 by edejimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*rtrn;

	rtrn = malloc(size * count);
	if (!rtrn)
		return (NULL);
	ft_memset(rtrn, 0, size * count);
	return (rtrn);
}
