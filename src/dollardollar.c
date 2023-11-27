
#include "minishell.h"

# define SCRIPT  "script_pgrep"
/*
 * Idea of create a file in order to run a bash script of pgrep because we want
 * to get the PID of the minishell due to 42macos can not execve the command
 * pgrep minishell
 * So, first open a file descriptor to write in it the script, then fork to
 * execve /bin/bash + script, finally parent unlik file.
 *
 * [x]Problem with two or more mininshell running, this prints all pid
 * [x]Get the last line, not null;
 */
void	dollardollar(t_ms * ms, char **envp)
{
	int		fd;
	pid_t	pid;
	const char *script_cmd = "#!/bin/bash\npgrep minishell";	
	const char *cmd[] = {"/bin/bash", SCRIPT, 0};
	char	*line;

	printf(YEL"Strat dollar dollar test\n"RST);
	fd = open(SCRIPT, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd < 0)
		ft_putendl_fd("Error creating script file", 2);
	ft_putstr_fd((char *)script_cmd, fd);
	close(fd);
	fd = open(PID_BUFFER, O_CREAT | O_TRUNC | O_RDWR, 0777);
	pid = fork();
	if (!pid)
	{
		write(1, "Child\n", 6);
		dup2(fd, STDOUT_FILENO);
		if(execve(cmd[0], (char **)cmd, envp) == -1)
			printf("*+EXECVE FAILED+*\n");
		exit(0);
	}
	else
	{
		close(fd);
		waitpid(pid, 0, 0);
		write(1, "Father\n", 7);
		fd = open(PID_BUFFER, O_RDWR);
		//ms->pid = get_next_line(fd);
		//*ft_strrchr(ms->pid, '\n') = 0;
		line = get_next_line(fd);
		printf("LINE %s\n", line);
		ms->pid = NULL;
		while (line != NULL)
		{
			free(ms->pid);
			ms->pid = ft_strdup(line);
			free(line);
			line = get_next_line(fd);
		}
		if (ms->pid)
			*ft_strrchr(ms->pid, '\n') = 0;
		printf("PID %s\n", ms->pid);
		close(fd);
		unlink(SCRIPT);
		unlink(PID_BUFFER);
	}
	printf(YEL"End dollar dollar test\n"RST);
}
