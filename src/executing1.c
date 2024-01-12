
#include "minishell.h"

/*
t_lexer_token	*str_export(t_lexer_token *ltoken)
{
	while (ltoken)
	{
		
	}
}
*/

/* IDEA LÓGICA
	while mientras exista ltoken
		if si ltoken es igual a export
			if si existe el siguiente
				ltoken = ltoken->next
				ft_export(ms, ltoken->arg, 0);
				ltoken = ltoken->next;
			else
				ft_export(ms, NULL, 1);
		else
		ltoken no tiene export
			ft_export(ms, ltoken->arg, 2)
			ltoken = ltoken->next;

	Hay que tener en cuenta lo siguiente
	si una variable ya está exportada en env por ejemplo hola=mundo
	si lanzamos lo siguiente en bash:
	hola=adios
	entra por el ltoken no tiene export, es decir scope 2, pero
	el scope de la variable $hola es 0, osea que no debe cambiar su scope, 
	pero si debe modificar su valor.

	otro caso para codificar es:
	primera vez por ejemplo:
	hola=mundo
	esto va por el camnio ltoken no tiene export
	se guarda para declare, pero si a continuación se ejecuta
	export hola
	hola=mundo que esta en declare con el scope 2 debe cambiar a 0

	otro caso para codificar es:
	si lanzamos el siguiente comando
	export hola
	este va por el camino ltoken existe por el scope 1
	si se ejecuta a continuacion:
	hola=mundo
	automaticamnete al setearla con el = entra por el camino de no tiene export
	pero este si se exporta a env automaticamente osea que scope pasa a 0 y has equal = 1;
*/
/*
 * Scope:
 * 0 = env;
 * 1 = export;
 * 2 = declare;
 */
int	execute_export(t_ms *ms, t_lexer_token *ltoken)
{
	t_lexer_token	*tmp;
	int				status;

	tmp = ltoken;
	while (tmp)
	{
		if(!ft_strncmp(tmp->arg, "export", ft_strlen(tmp->arg) + 1))
		{
			if (tmp->next)
			{
				tmp = tmp->next;
				status = ft_export(ms, tmp->arg, 1);
			}
			else
				status = ft_export(ms, NULL, 2);
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
	return (status);
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

int	execute_unset(t_ms *ms, t_lexer_token *ltoken)
{
	t_lexer_token	*tmp;
	int				status;

	if (ltoken->next)
	{
		tmp = ltoken->next;
		while (tmp)
		{
			status = ft_unset(ms, tmp->arg);
			tmp = tmp->next;
		}
	}
	else
		status = ft_unset(ms, NULL);
	return (status);
}
