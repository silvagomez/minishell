
#include "minishell.h"

void	ft_cd(t_ms *ms)
{
	int		cd_status;
	//char	*path;

	printf(GRN"ENTRO\n");
	if (!ms->lexer_token->next)
	{
		printf("CASE null  We need to go to HOME\n");
		cd_status = chdir(ft_getenv(ms, "HOME"));
		//return ;
	}
	else if (*(ms->lexer_token->next->arg) == '-')
	{
		printf("CASE - We need to go to OLDPWD\n");
		cd_status = chdir(ft_getenv(ms, "OLDPWD"));
		//return ;
	}
	else
	{
		printf("change dir %s\n", ms->lexer_token->next->arg);
		cd_status = chdir(ms->lexer_token->next->arg);
		//return ;
	}
	if (cd_status != 0)
		ft_putendl_fd("Error", 2);
	printf(BLU"status %i\n", cd_status);

	char	pwd[1024];
	
	if (getcwd(pwd, sizeof(pwd)))
		printf("%s\n", pwd);
	else
		ft_putendl_fd("ERRRRRRRROOOOOORRRR", 2);
}
