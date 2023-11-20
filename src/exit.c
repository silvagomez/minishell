
#include "minishell.h"

void    free_exit(t_ms *ms)
{
    t_envlst    *tmp;
    free (ms->pwd_ppt);
    free (ms->pwd);
    free (ms->user);
    free (ms->home);
    free (ms->shadow);
    tmp = ms->envlst;
    while (tmp)
        {
            tmp = ms->envlst->next;
            free (ms->envlst->name);
            free (ms->envlst->content);
            free (ms->envlst);
            ms->envlst = tmp;
        }
    //LIBERADO HASTA FALLO DE SHADOW
}