
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "signal.h"
# include <fcntl.h>

typedef struct s_envlst{
	struct s_envlst	*next;
	struct s_envlst	*prev;
	char			*name;
	char			*content;
}				t_envlst;

typedef struct s_strlst{
	char			*str;
	size_t			index;
	struct s_strlst	*next;
	
}				t_strlst;

typedef struct s_lexer_token
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
	struct s_lexer_token	*next;
}				t_lexer_token;

typedef struct s_ms{
	char			*prompt;
	char			*rline;
	char			*shadow;
	char			*user;
	char			*home;
	char			*pwd;
	char			*pwd_ppt;
	char			quote;
	int				pipe_qty;
	t_lexer_token	*lexer_token;
	t_strlst		*str_lst;
	t_envlst		*envlst;
	
}				t_ms;

//ENVP FUNCS
size_t		exist_envp(char **envp);
void		fill_envp(t_ms *ms, char **envp);
void		set_paths(t_ms *ms);
t_envlst	*envlst_last(t_envlst *lst);
void		envlst_add(t_envlst **lst, t_envlst *new_node);
t_envlst	*envlst_new(t_ms *ms, char *line);
char		*ft_getenv(t_ms *ms, char *var_name);

//BUILTIN FUNCS
void		ft_env(t_ms *ms);
void		ft_unset(t_ms *ms, char *var_name);
void		ft_export(t_ms *ms, char *arg);
void		ft_pwd(t_ms *ms);

//PROMPT FUNCS
void	set_prompt(t_ms *ms);


//QUOTING FUNCS
void	check_quote_char(t_ms *ms);
int		is_valid_quoting(t_ms *ms);

//REDIRECTING FUNCS
void	append_output(char *content, char *filename);

//PARSING FUNCS
void	count_pipes(t_ms *ms);
void	create_shadow(t_ms *ms);
void 	tokenize_rline(t_ms *ms);

//EXPANSION FUNCS
void	expand_test(t_ms *ms);

//EXIT FUNCS
void    free_exit(t_ms *ms);

//COLORS
#define BLACK		"\033[90m"
#define BLACK2		"\033[30m"
#define RED			"\033[91m"
#define RED2		"\033[31m"
#define GREEN 		"\033[92m"
#define YELLOW		"\033[93m"
#define BLUE		"\033[94m"
#define MAGENTA		"\033[95m"
#define MAGENTA2	"\033[35m"
#define WHITE		"\033[97m"
#define RESET		"\033[0m"

#endif
