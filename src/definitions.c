/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:09:11 by codespace         #+#    #+#             */
/*   Updated: 2023/11/08 11:46:35 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*g_type[12] = {"command", "flag", "pipe", "builtin", \
	"redirection1", "redirection2", "redirection3", "expansion", "substitution", \
	"variable_assign", "arithmetic", "forbidden"};

const char	*g_builtin[7] = {"echo", "cd", "pwd", "export", "unset", "env", \
	"exit"};
