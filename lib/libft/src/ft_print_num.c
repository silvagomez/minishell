/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_num.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edejimen <edejimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 12:46:03 by edejimen          #+#    #+#             */
/*   Updated: 2023/06/12 13:34:51 by edejimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_print_num(int num)
{
	char	*aux;
	int		count;

	aux = ft_itoa(num);
	count = ft_print_str(aux);
	free(aux);
	return (count);
}
