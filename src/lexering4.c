
#include "../include/minishell.h"

void	print_flags_if_present(t_lexer_token *token)
{
	if (token->tag_program)
		printf(GRN"\t(PROGRAM: %zu)"RST, token->tag_program);
	if (token->tag_builtin)
		printf(GRN"\t(BUILTIN: %zu)"RST, token->tag_builtin);
	if (token->tag_double_q)
		printf(GRN"\t(DOUBLE_Q: %zu)"RST, token->tag_double_q);
	if (token->tag_single_q)
		printf(GRN"\t(SINGLE_Q: %zu)"RST, token->tag_single_q);
	if (token->tag_redir)
		printf(GRN"\t(REDIR: %zu)"RST, token->tag_redir);
	if (token->tag_pipe)
		printf(GRN"\t(PIPE: %zu)"RST, token->tag_pipe);
	if (token->tag_spec_char)
		printf(GRN"\t(SPEC_CHAR: %zu)"RST, token->tag_spec_char);
}
