
#include "minishell.h"

void	clear_command(void)
{
	int	fd;
	const char	*script_cmd1 = "#!/bin/bash\nclear";

	fd = open(SCRIPT_CLEAR, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd < 0)
		error_handling(ERR_ONFD, EXIT_FAILURE);
	ft_putstr_fd((char *)script_cmd1, fd);
	close(fd);
}

void	ft_clear(char **envp)
{
	int			status;
	pid_t		pid;
	const char	*cmd[] = {"/bin/bash", SCRIPT_CLEAR, 0};

	clear_command();
	pid = fork();
	if (!pid)
	{
		if (execve(cmd[0], (char **)cmd, envp) == -1)
			error_handling(ERR_EXEC, EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &status, 0);
		unlink(SCRIPT_CLEAR);
		g_status = status;
	}
}
