
#include "minishell.h"

void	ft_cd(t_ms *ms)
{
	int	cd_status;

	printf(GRN"ENTRO\n");
	if (!(ms->str_lst->next))
		printf("I need to go to $HOME");
	printf("change dir %s\n", ms->str_lst->next->str);
	cd_status = chdir(ms->str_lst->next->str);//JOIN PENDIENTE
	if (cd_status != 0)
		ft_putendl_fd("Error", 2);
	printf(BLU"status %i\n", cd_status);

	char	pwd[1024];
	
	if (getcwd(pwd, sizeof(pwd)))
		printf("%s\n", pwd);
	else
		ft_putendl_fd("ERRRRRRRROOOOOORRRR", 2);
}
