
#include "../include/minishell.h"

/*
 * Debuging function 
 */
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

/*
 * Debuging function 
 */
void	print_lexer_tokens(t_ms *ms)
{
	t_lexer_token	*tmp;

	printf("\nLEXER TOKENS: %i\n", lexer_token_count(ms->lexer_token));
	tmp = ms->lexer_token;
	while (tmp)
	{
		if (tmp->init_pos <= tmp->end_pos)
		{
			printf("\n#%zu: "HYEL"%s - From %i to %i"RST"", \
					tmp->token_id, tmp->arg, tmp->init_pos, tmp->end_pos);
			print_flags_if_present(tmp);
		}
		tmp = tmp->next;
	}
}

/*
 * Lexer token tagging
 */
void	tag_token(t_ms *ms, char c, int init, int i)
{
	if (c == '|')
		(lexer_token_last(ms->lexer_token))->tag_pipe = 1;
	if (c == '>' || c == '<')
	{
		(lexer_token_last(ms->lexer_token))->tag_redir += 1;
		if (c == '>')
			(lexer_token_last(ms->lexer_token))->tag_redir += 2;
		if (init != (i - 1))
			(lexer_token_last(ms->lexer_token))->tag_redir += 1;
	}
	if (c == '"')
		(lexer_token_last(ms->lexer_token))->tag_double_q = 1;
	if (c == '\'')
		(lexer_token_last(ms->lexer_token))->tag_single_q = 1;
}

void	tokenize_rline_case1(t_ms *ms, int *i, int init)
{
	char	c;

	c = ms->rline[*i];
	while (ms->rline[*i] && ms->rline[*i] == c)
	{
		(*i)++;
		if (c == '|')
			break ;
	}
	lexer_token_add(&ms->lexer_token, lexer_token_new(ms, init, *i - 1));
	if (ms->lexer_token)
		tag_token(ms, c, init, *i);
}

void	tokenize_rline_case2(t_ms *ms, int *i, int init)
{
	char	c;

	c = ms->rline[*i];
	(*i)++;
	while ((ms->rline[*i] && ms->rline[*i] != c) || (ms->rline[*i] \
				&& ms->rline[*i] == c && ms->rline[*i - 1] == '\\'))
	(*i)++;
	//printf("I VALE: %i\n", *i);
	lexer_token_add(&ms->lexer_token, lexer_token_new(ms, init + 1, *i - 1));
	if (ms->lexer_token)
		tag_token(ms, c, init, *i);
	(*i)++;
}

void	tokenize_rline_case3(t_ms *ms, int *i, int init)
{
	while (ms->rline[*i] && ms->rline[*i] != ' ' && ms->rline[*i] != '\'' \
					&& ms->rline[*i] != '\t' && ms->rline[*i] != '"' \
					&& ms->rline[*i] != '|' && ms->rline[*i] != '<' \
					&& ms->rline[*i] != '>')
		(*i)++;
	lexer_token_add(&ms->lexer_token, lexer_token_new(ms, init, *i - 1));
}

/*
 * Converts the expanded rline into lexer tokens. 
 * ¡¡Needs refactoring or modularizing!!
 */
void tokenize_rline(t_ms *ms)
{
	int			i;
	int			init;

	i = 0;
	//printf("EXPANDED RLINE: %s\n", ms->rline);
	ms->lexer_token = NULL;
	while (ms->rline[i])
	{
		while (ms->rline[i] == ' ' || ms->rline[i] == '\t')
			i++;
		init = i;
		if (ms->rline[i] == '|' || ms->rline[i] == '>' || ms->rline[i] == '<')
			tokenize_rline_case1(ms, &i, init);
		else if (ms->rline[i] == '"' || ms->rline[i] == '\'')
			tokenize_rline_case2(ms, &i, init);
		else
			tokenize_rline_case3(ms, &i, init);
	}
	//LEXER TOKENS DEFINIDOS
	join_lexer_tokens(ms);
	//print_lexer_tokens(ms);
}
