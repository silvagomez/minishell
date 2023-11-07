/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:09:11 by codespace         #+#    #+#             */
/*   Updated: 2023/11/07 16:22:22 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char	*g_type[12] = {"command", "flag", "pipe", "builtin", \
	"redirection1", "redirection2", "redirection3", "expasion", "subsitution", \
	"variable_asign", "aritmetic", "fordiben"};

const char	*g_builtin[7] = {"echo", "cd", "pwd", "export", "unset", "env", \
	"exit"};
