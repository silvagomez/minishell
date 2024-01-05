
#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
//# include <asm/termbits.h>

# include "dictionary.h"

typedef struct s_envlst
{
	struct s_envlst	*next;
	struct s_envlst	*prev;
	char			*name;
	size_t			has_equal;
	size_t			scope;
	char			*content;
}				t_envlst;

typedef struct s_strlst
{
	char			*str;
	size_t			index;
	struct s_strlst	*next;	
}				t_strlst;

typedef struct s_hdlst
{
	char			*str;
	struct s_hdlst	*next;	
}				t_hdlst;

typedef struct s_lexer_token
{
	int						init_pos;
	int						end_pos;
	char					*arg;
	size_t					tag_program;
	size_t					tag_builtin;
	size_t					tag_double_q;
	size_t					tag_single_q;
	size_t					tag_redir;
	size_t					tag_pipe;
	size_t					tag_spec_char;
	size_t					token_id;
	struct s_lexer_token	*next;
	struct s_lexer_token	*prev;
}				t_lexer_token;

typedef struct s_parser_token
{
	t_lexer_token			*lxr_list;
	t_hdlst					*hd_list;
	size_t					token_id;
	size_t					is_builtin;
	char					*hd_str;
	char					*hd_line;
	int						hd_pipe[2];
	int						output_fd;
	int						input_fd;
	int						is_input;
	int						is_output;
	int						is_here_doc;
	int						default_stdin;
	int						default_stdout;
	struct s_parser_token	*next;
	struct s_parser_token	*prev;
}				t_parser_token;

typedef struct s_ms
{
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
	int				*tube;
	int				pipe_qty;
	int				dflt_input;
	int				dflt_output;
	t_lexer_token	*lexer_token;
	t_parser_token	*parser_token;
	t_strlst		*str_lst;
	t_envlst		*envlst;	
}				t_ms;

/*-ENVP FUNCS ---------------------------------------------------------------*/
size_t			exist_envp(char **envp);
void			fill_envp(t_ms *ms, char **envp);
void			set_default_paths(t_ms *ms, char **envp);
t_envlst		*envlst_last(t_envlst *lst);
void			envlst_add(t_envlst **lst, t_envlst *new_node);
t_envlst		*envlst_new(t_ms *ms, char *line);
char			*ft_getenv(t_ms *ms, char *var_name);
t_envlst		*find_env(t_ms *ms, char *env_name);
void			update_env_content(t_ms *ms, char *env_name, char *s);
void			update_env_wd(t_ms *ms, char *env_name, char *arg);
void			envlist_to_array(t_ms *ms, size_t command);
size_t			size_for_array_envp(t_ms *ms);
int				envlst_node_count(t_envlst	*lst);

/*-BUILTIN FUNCS ------------------------------------------------------------*/
//----env--------//
void			ft_env(t_ms *ms);
void			update_env_content(t_ms *ms, char *env_name, char *s);
t_envlst		*find_env(t_ms *ms, char *env_name);
char			*ft_getenv(t_ms *ms, char *var_name);
//----unset-----//
void			ft_unset(t_ms *ms, char *var_name);
//void			ft_unset(t_ms *ms, t_lexer_token *ltoken);
//----export----//
//void			ft_export(t_ms *ms, char *arg);
void			ft_export(t_ms *ms, char *arg, size_t scope);
//void			ft_export(t_ms *ms, t_lexer_token *ltoken);
//----pwd-------//
void			ft_pwd(t_ms *ms);
//----cd--------//
void			ft_cd(t_ms *ms, t_lexer_token *token);
//----echo------//
void			ft_echo(t_ms *ms, t_parser_token *ptoken, t_lexer_token *ltoken);

/*-PROMPT FUNCS -------------------------------------------------------------*/
void			set_prompt(t_ms *ms);

/*-QUOTING FUNCS ------------------------------------------------------------*/
void			check_quote_char(t_ms *ms);
int				is_valid_quoting(t_ms *ms);

/*-REDIRECTING FUNCS --------------------------------------------------------*/
void			check_redirs(t_parser_token *ptoken);

/*-LEXERING FUNCS -----------------------------------------------------------*/
void			fill_shadow(t_ms *ms, int *i, char quote);
int				create_shadow(t_ms *ms);
t_lexer_token	*lexer_token_last(t_lexer_token *lst);
void			lexer_token_add(t_lexer_token **lst, t_lexer_token *new_node);
int				lexer_token_count(t_lexer_token *lst);
t_lexer_token	*lexer_token_new(t_ms *ms, int init_pos, int end_pos);
void			print_flags_if_present(t_lexer_token *token);
void			tag_token(t_ms *ms, char c, int init, int i);
void			tokenize_rline(t_ms *ms);
t_strlst		*strlst_last(t_strlst *lst);
void			strlst_add(t_strlst **lst, t_strlst *new_node);
t_strlst		*strlst_new(t_ms *ms, int init_pos, int end_pos);
void			rline_to_lst(t_ms *ms);
void			free_str_lst(t_strlst *list);
void			expand_lst(t_ms *ms);
void			expand_test(t_ms *ms);

/*-PARSING FUNCS ------------------------------------------------------------*/
t_parser_token	*parser_token_last(t_parser_token *lst);
void			parser_token_add(t_parser_token **lst, \
				t_parser_token *new_node);
int				parser_token_count(t_parser_token *lst);
t_parser_token	*parser_token_new(t_ms *ms, t_lexer_token *lexer_token);
void			tokenize_parser(t_ms *ms);
void			token_piping(t_ms *ms, t_parser_token *ptoken);
size_t			is_local_export(char *arg);

/*-EXECUTING FUNCS ----------------------------------------------------------*/
int				is_builtin(char *arg);
void			execute_builtin(t_ms *ms, t_parser_token *ptoken, \
				t_lexer_token *ltoken);
void			execute_program(t_ms *ms, t_parser_token *token);
void			execute_token(t_ms *ms, t_parser_token *token);
void			env_to_path(t_ms *ms, t_envlst *envlst);
int				get_command(t_ms *ms, t_parser_token *ptoken);
void			execute_export(t_ms *ms, t_lexer_token *ltoken);
void			execute_unset(t_ms *ms, t_lexer_token *ltoken);

/*-HERE_DOC FUNCS -----------------------------------------------------------*/
t_hdlst			*hdlst_last(t_hdlst *lst);
void			hdlst_add(t_hdlst **lst, t_hdlst *new_node);
int				hdlst_count(t_hdlst *lst);
t_hdlst			*hdlst_new(char *str);
void			hdlst_delete(t_parser_token *ptoken, t_hdlst *node);
void			manage_heredoc(t_parser_token *ptoken);
void			hd_child(t_parser_token *ptoken);
void			hd_father(t_parser_token *ptoken);

/*-EXPANSION FUNCS ----------------------------------------------------------*/
void			expand_test(t_ms *ms);

/*-EXIT FUNCS ---------------------------------------------------------------*/
void			free_exit(t_ms *ms);

/*-FREEING FUNCS ------------------------------------------------------------*/
void			free_string_array(char **array);
void			free_envlst(t_envlst *envlst);
void			free_lexer_list(t_lexer_token *ltoken);
void			free_parser_list(t_parser_token *ptoken);
void			free_per_prompt(t_ms *ms);
void			free_per_instance(t_ms *ms);

/*-SIGNALS ------------------------------------------------------------------*/
void			set_signal_action(int action);

/*-IDEAS --------------------------------------------------------------------*/
void			dollardollar(t_ms *ms, char **envp);

#endif
