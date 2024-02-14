
#include "minishell.h"

/*
 * This functions allocates memory to a **array in the case of a bin-command
 */
void	create_array(t_ms *ms, t_lexer_token *ltoken)
{
	t_lexer_token	*ltmp;
	int				i;

	ms->cmd_array = malloc(sizeof(char *) * (lexer_token_count(ltoken) + 1));
	ltmp = ltoken;
	i = 0;
	while (ltmp)
	{
		ms->cmd_array[i] = ltmp->arg;
		i++;
		ltmp = ltmp->next;
	}
	ms->cmd_array[i] = NULL;
}

/*
 * This function seeks in pathlist if the arg is a binary program (command)
 */
int	get_command(t_ms *ms, t_parser_token *ptoken)
{
	int	i;

	i = -1;
	while (ms->pathlist[++i])
	{
		free (ms->cmd);
		ms->cmd = ft_strjoin(ms->pathlist[i], ptoken->lxr_list->arg);
		if (access(ms->cmd, F_OK) == 0)
		{
			free(ms->cmd_array[0]);
			ms->cmd_array[0] = ft_strdup(ms->cmd);
			break ;
		}
	}
	if (ms->pathlist[i] == NULL)
	{
		if (access(ptoken->lxr_list->arg, F_OK) == 0)
		{
			free (ms->cmd); //TESTEAR CON RUTA ABSOLUTA DE PROGRAMAS!!
			ms->cmd = ptoken->lxr_list->arg;
		}
		else
			return (0);
	}
	return (1);
}
/*
 * This function checks is ptoken->arg is a binary program (command)
 */
void	check_command(t_ms *ms, t_parser_token *ptoken)
{
	if (ptoken->tag == 0)
	{
		if (!get_command(ms, ptoken))
			error_handling_exit(ERR_CNOF, 127);
	}
}
