
#include "minishell.h"

int	is_local_var(t_lexer_token *ltoken)
{
	printf(HRED"VERIFY IF IS LOCAL %s\n"RST, ltoken->arg);
	if (ft_strchr(ltoken->arg, '='))
		return (1);
	return (0);
}
/* IDEA LÓGICA
	while mientras exista ltoken
		if si ltoken es igual a export
			if si existe el siguiente
				ltoken = ltoken->next
				ft_export(ms, ltoken->arg, 1);
				ltoken = ltoken->next;
			else
				ft_export(ms, NULL, 2);
		else
		ltoken no tiene export
			ft_export(ms, ltoken->arg, 0)
			ltoken = ltoken->next;
*/
/*
t_lexer_token	*str_export(t_lexer_token *ltoken)
{
	while (ltoken)
	{
		
	}
}
*/
void	execute_export(t_ms *ms, t_lexer_token *ltoken)
{
	t_lexer_token	*tmp;

	tmp = ltoken;
	while (tmp)
	{
		printf("token id is %lu of %s\n", tmp->token_id, tmp->arg);
		if(!ft_strncmp(tmp->arg, "export", ft_strlen(tmp->arg) + 1))
		{
			if (tmp->next)
			{
				tmp = tmp->next;
				ft_export(ms, tmp->arg, 1);
			}
			else
				ft_export(ms, NULL, 2);
		}
		else
		{
			//falta el caso de export a=b a1=b export a2=b, aqui deberia añadir los export a env y el del medio a export a secas
			if (tmp->next && !ft_strncmp(tmp->next->arg, "export", ft_strlen(tmp->arg) + 1))
				;
			else
				ft_export(ms, tmp->arg, 0);
		}
		tmp = tmp->next;
	}

/* LAST IDEA FROM 2023
	if (ltoken->next)
	{
		tmp = ltoken->next;
		while (tmp)
		{
			ft_export(ms, tmp->arg, scope);
			tmp = tmp->next;
		}
	}
	else
		ft_export(ms, NULL, 1);
*/
}

void	execute_unset(t_ms *ms, t_lexer_token *ltoken)
{
	t_lexer_token	*tmp;

	if (ltoken->next)
	{
		tmp = ltoken->next;
		while (tmp)
		{
			ft_unset(ms, tmp->arg);
			tmp = tmp->next;
		}
	}
	else
		ft_unset(ms, NULL);
}
