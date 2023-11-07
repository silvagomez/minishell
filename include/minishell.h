/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:52:26 by codespace         #+#    #+#             */
/*   Updated: 2023/11/07 16:53:24 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"
# include "signal.h"
# include <fcntl.h>

typedef struct s_token_pos
{
	int					init_pos;
	int					end_pos;
	struct s_token_pos	*next;
}				t_token_pos;

typedef struct s_ms{
	char		*prompt;
	char		*shadow;
	char		quote;
	int			pipe_qty;
	t_token_pos	*token_pos;
}				t_ms;

//QUOTING FUNCS
void	check_quote_char(t_ms *ms);
int		is_valid_quoting(t_ms *ms);

//REDIRECTING FUNCS
void	append_output(char *content, char *filename);

//PARSING FUNCS
void	count_pipes(t_ms *ms);
void	create_shadow(t_ms *ms);
void 	tokenize_prompt(t_ms *ms);

//COLORS
#define BLACK	"\033[90m"
#define BLACK2	"\033[30m"
#define RED		"\033[91m"
#define RED2	"\033[31m"
#define GREEN 	"\033[92m"
#define YELLOW	"\033[93m"
#define BLUE	"\033[94m"
#define MAGENTA	"\033[95m"
#define RESET	"\033[0m"

#endif
