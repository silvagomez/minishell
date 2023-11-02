/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:52:26 by codespace         #+#    #+#             */
/*   Updated: 2023/11/02 16:59:18 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"

typedef struct s_ms{
	char	*prompt;
	char	quote;
}				t_ms;

//QUOTING FUNCS
void	check_quote_char(t_ms *ms);
int		is_valid_quoting(t_ms *ms);

#endif
