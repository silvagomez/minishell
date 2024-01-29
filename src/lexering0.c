
#include "../include/minishell.h"

/*
 * Auxiliary function for "create_shadow" to make the code more modular
 */
void	fill_shadow(t_ms *ms, int *i, char quote)
{
	if (quote == '\'')
		ms->shadow[(*i)++] = '1';
	else
		ms->shadow[(*i)++] = '2';
}

void	define_spaces_in_shadow(t_ms *ms)
{
	int	i;

	i = -1;
	while (ms->rline && ms->rline[++i])
		{
			if (ms->rline[i] == ' ' && ms->shadow[i] != '1' \
					&& ms->shadow[i] != '2')
				ms->shadow[i] = '8';
		}
}

/*
 * Function that creates the shadow string. +4 lines that will be removed later
 */
int	create_shadow(t_ms *ms)
{
	int		i;
	char	quote;

	i = 0;
	if (ms->rline)
		ms->shadow = calloc(sizeof(char), (ft_strlen(ms->rline) + 1));
	if (ms->rline)
		ft_memset(ms->shadow, '0', ft_strlen(ms->rline));
	while (ms->rline && ms->rline[i])
	{
		if (ms->rline[i] == '"' || ms->rline[i] == '\'')
		{
			quote = ms->rline[i];
			fill_shadow(ms, &i, quote);
			while ((ms->rline[i] && ms->rline[i] != quote) || (ms->rline[i] && ms->rline[i] == quote && ms->rline[i - 1] == '\\'))
				fill_shadow(ms, &i, quote);
			if (!ms->rline[i])
			{
				ms->shadow[i] = 'E';
				return (ft_printf(HRED"ERROR COMILLAS SIN CERRAR\n"RST), 0);
			}
			fill_shadow(ms, &i, quote);
		}
		else
			i++;
	}
	define_spaces_in_shadow(ms);
	printf("\nSHADOW: %s\n", ms->shadow);
	return (1);
}
