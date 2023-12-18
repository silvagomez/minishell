
#include "minishell.h"

/*
 * $0 is the name of the running process. If we use it inside of a shell it
 * will return the name of the shell. If we use it inside of a script,
 * it will be the name of the script
 *
 * We need to export a env var with the name of the running process, in this 
 * case minishell.
 */
void	dollarzero(t_ms *ms)
{
	ft_export(ms, "MINI=minishell");
	//ms->dollarzero = ft_strdup("minishell");
}
