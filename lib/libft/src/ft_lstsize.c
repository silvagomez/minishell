/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edejimen <edejimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:56:21 by edejimen          #+#    #+#             */
/*   Updated: 2023/05/11 15:23:56 by edejimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	items;

	items = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		items++;
	}
	return (items);
}
