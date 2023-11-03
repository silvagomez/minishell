/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 21:54:02 by codespace         #+#    #+#             */
/*   Updated: 2023/11/03 13:10:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_output(char *content, char *filename)
{
	int	fd;

	fd = open(filename, O_APPEND | O_RDWR | O_CREAT, 0777);
	ft_putstr_fd(content, fd);
	close(fd);
}

void	redirect_output(char *content, char *filename)
{
	int	fd;

	fd = open(filename, O_TRUNC | O_RDWR | O_CREAT, 0777);
	ft_putstr_fd(content, fd);
	close(fd);
}

void	redirect_input(char *content)
{
	ft_putstr_fd(content, 0);
}
