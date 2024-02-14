
#include "minishell.h"

void	free_all_hd_lists(t_ms *ms)
{
	t_parser_token	*ptmp;
	t_hdlst			*hdtmp;
	t_hdlst			*hdnext;

	ptmp = ms->parser_token;
	while (ptmp)
	{
		hdtmp = ptmp->hd_list;
		while (hdtmp)
		{
			hdnext = hdtmp->next;
			hdlst_delete(ptmp, hdtmp);
			hdtmp = hdnext;
		}
		ptmp = ptmp->next;
	}
}

void	free_per_prompt(t_ms *ms)
{
	free(ms->prompt);
	ms->prompt = NULL;
	free(ms->rline);
	ms->rline = NULL;
	free(ms->shadow);
	ms->shadow = NULL;
	free(ms->pwd_ppt);
	ms->pwd_ppt = NULL;
	free(ms->tube);
	ms->tube = NULL;
	if (ms->cmd_array)
	{
		free(ms->cmd_array);
		ms->cmd_array = 0;
	}
	free_all_hd_lists(ms);
	if (ms->parser_token)
		free_parser_list(ms->parser_token);
	ms->parser_token = NULL;
}

void	free_per_instance(t_ms *ms)
{
	free_string_array(ms->envp);
	free_string_array(ms->pathlist);
	free(ms->pwd);
	free(ms->user);
	free(ms->home);
	free(ms->pid);
	free(ms->os_name);
	free_envlst(ms->envlst);
	close (ms->dflt_input);
	close (ms->dflt_output);
}
