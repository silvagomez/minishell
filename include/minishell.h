
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include "signal.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# define PID_BUFFER "temp"

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
	char				*arg;
	size_t				tag_program;
	size_t				tag_builtin;
	size_t				tag_double_q;
	size_t				tag_single_q;
	size_t				tag_redir;
	size_t				tag_pipe;
	size_t				tag_flag;
	size_t				tag_spec_char;
	size_t				token_id;
	struct s_lexer_token	*next;
	struct s_lexer_token	*prev;
}				t_lexer_token;

typedef struct s_parser_token
{
	t_lexer_token			*lxr_list;
	size_t					token_id;
	int						output_fd;
	int						input_fd;
	struct s_parser_token	*next;
	struct s_parser_token	*prev;
}				t_parser_token;

typedef struct s_ms{
	char			**cmd_array;
	char			**envp;
	char			**pathlist;
	char			*prompt;
	char			*rline;
	char			*shadow;
	char			*user;
	char			*home;
	char			*pwd;
	char			*pwd_ppt;
	char			*pid;
	char			*cmd;
	char			*os_name;
	char			quote;
	int				pipe_qty;
	t_lexer_token	*lexer_token;
	t_parser_token	*parser_token;
	t_strlst		*str_lst;
	t_envlst		*envlst;
	
}				t_ms;

//ENVP FUNCS
size_t		exist_envp(char **envp);
void		fill_envp(t_ms *ms, char **envp);
void		set_default_paths(t_ms *ms, char **envp);
t_envlst	*envlst_last(t_envlst *lst);
void		envlst_add(t_envlst **lst, t_envlst *new_node);
t_envlst	*envlst_new(t_ms *ms, char *line);
char		*ft_getenv(t_ms *ms, char *var_name);
t_envlst	*find_env(t_ms *ms, char *env_name);
void		update_env_content(t_ms *ms, char *env_name, char *s);
void		update_env_wd(t_ms *ms, char *env_name, char *arg);

//BUILTIN FUNCS
void		ft_env(t_ms *ms);
void		ft_unset(t_ms *ms, char *var_name);
void		ft_export(t_ms *ms, char *arg);
void		ft_pwd(t_ms *ms);
void		ft_cd(t_ms *ms, t_lexer_token *token);
void		ft_echo(t_parser_token *ptoken, t_lexer_token *ltoken);

//PROMPT FUNCS
void	set_prompt(t_ms *ms);


//QUOTING FUNCS
void	check_quote_char(t_ms *ms);
int		is_valid_quoting(t_ms *ms);

//REDIRECTING FUNCS
void	check_redirs(t_parser_token *ptoken);

//LEXERING FUNCS
void			fill_shadow(t_ms *ms, int *i, char quote);
int				create_shadow(t_ms *ms);
t_lexer_token	*lexer_token_last(t_lexer_token *lst);
void			lexer_token_add(t_lexer_token **lst, t_lexer_token *new_node);
int				lexer_token_count(t_lexer_token *lst);
t_lexer_token	*lexer_token_new(t_ms *ms, int init_pos, int end_pos);
void			print_flags_if_present(t_lexer_token *token);
void			tag_token(t_ms *ms, char c, int init, int i);
void 			tokenize_rline(t_ms *ms);
t_strlst		*strlst_last(t_strlst *lst);
void			strlst_add(t_strlst **lst, t_strlst *new_node);
t_strlst		*strlst_new(t_ms *ms, int init_pos, int end_pos);
void			rline_to_lst(t_ms *ms);
void			free_str_lst(t_strlst *list);
void			expand_lst(t_ms *ms);
void			expand_test(t_ms *ms);

//PARSING FUNCS
t_parser_token	*parser_token_last(t_parser_token *lst);
void			parser_token_add(t_parser_token **lst, t_parser_token *new_node);
int				parser_token_count(t_parser_token *lst);
t_parser_token	*parser_token_new(t_ms *ms, t_lexer_token *lexer_token);
void 			tokenize_parser(t_ms *ms);

//EXECUTING FUNCS
int		is_builtin(char *arg);
void	execute_builtin(t_ms *ms, t_parser_token *ptoken, t_lexer_token *ltoken);
void	execute_program(t_ms *ms, t_parser_token *token);
void 	execute_token(t_ms *ms, t_parser_token *token);
void	env_to_path(t_ms *ms, t_envlst *envlst);
int		get_command(t_ms *ms, t_parser_token *ptoken);
void	execute_export(t_ms *ms, t_lexer_token *ltoken);

//EXPANSION FUNCS
void	expand_test(t_ms *ms);

//EXIT FUNCS
void    free_exit(t_ms *ms);

//IDEAS
void	dollardollar(t_ms * ms, char **envp);

//COLOR
#define BLK		"\033[30m"
#define RED		"\033[31m"
#define GRN		"\033[32m"
#define YEL		"\033[33m"
#define BLU		"\033[34m"
#define MAG		"\033[35m"
#define CYN		"\033[36m"
#define WHT		"\033[37m"
#define RST		"\033[0m"

//HIGH COLOR
#define HBLK	"\033[90m"
#define HRED	"\033[91m"
#define HGRN	"\033[92m"
#define HYEL	"\033[93m"
#define HBLU	"\033[94m"
#define HMAG	"\033[95m"
#define HCYN	"\033[96m"
#define HWHT	"\033[97m"

#endif
