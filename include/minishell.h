
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "signal.h"
# include <fcntl.h>

/* typedef struct s_lst_expand
{
	size_t	id;
	char	*str;
	struct 
}; */

typedef struct s_strlst{
	char			*str;
	size_t			index;
	struct s_strlst	*next;
	
}				t_strlst;

typedef struct s_token_pos
{
	int					init_pos;
	int					end_pos;
	size_t				tag_command;
	size_t				tag_builtin;
	size_t				tag_double_q;
	size_t				tag_simple_q;
	size_t				tag_dollar;
	size_t				tag_redir;
	size_t				tag_pipe;
	size_t				tag_flag;
	size_t				tag_spec_char;
	size_t				token_id;
	//struct				*lst_expand;
	struct s_token_pos	*next;
}				t_token_pos;

typedef struct s_ms{
	char		*prompt;
	char		*shadow;
	char		**envp;
	char		quote;
	int			pipe_qty;
	t_token_pos	*token_pos;
	t_strlst	*str_lst;
	
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

//EXPANSION FUNCS
void	expand_test(t_ms *ms);

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
