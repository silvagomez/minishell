
#include "minishell.h"

/*
 * Create a file in order to run a bash script of pgrep because we want
 * to get the PID of the minishell due to 42macos can not execve the command
 * pgrep minishell.
 * We have discovered that pgrep does not work with execve.
 * So, first open a file descriptor to write in it the script, then fork to
 * execve /bin/bash + script, finally parent unlik file.
 *
 * [x]Problem with two or more mininshell running, this prints all pid
 * [x]Get the last line, not null;
 */

void	pid_command(t_ms *ms)
{
	int			fd;
	const char	*script_cmd1 = "#!/bin/bash\nps | sort -k 3 -r | ";
	const char	*script_cmd2 = "awk '{if ($4 == \"";
	const char	*script_cmd3 = "minishell\") print $1;}'";	

	fd = open(SCRIPT_PID, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd < 0)
		error_handling(ERR_ONFD, EXIT_FAILURE);
	ft_putstr_fd((char *)script_cmd1, fd);
	ft_putstr_fd((char *)script_cmd2, fd);
	if (!ft_strncmp("Darwin", ms->os_name, 5))
		ft_putstr_fd("./", fd);
	ft_putstr_fd((char *)script_cmd3, fd);
	close(fd);
}

void	minishell_pid(t_ms *ms)
{
	int			fd;
	char		*line;

	fd = open(PID_BUFFER, O_RDWR);
	if (fd < 0)
		error_handling(ERR_ONFD, EXIT_FAILURE);
	line = get_next_line(fd);
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
	close(fd);
}

void	unlink_script(void)
{
	unlink(SCRIPT_PID);
	unlink(PID_BUFFER);
}

void	dollardollar(t_ms *ms, char **envp)
{
	int			status;
	int			fd;
	pid_t		pid;
	const char	*cmd[] = {"/bin/bash", SCRIPT_PID, 0};

	pid_command(ms);
	fd = open(PID_BUFFER, O_CREAT | O_TRUNC | O_RDWR, 0777);
	if (fd < 0)
		error_handling(ERR_ONFD, EXIT_FAILURE);
	pid = fork();
	if (!pid)
	{
		dup2(fd, STDOUT_FILENO);
		if (execve(cmd[0], (char **)cmd, envp) == -1)
			error_handling(ERR_EXEC, EXIT_FAILURE);
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(fd);
		waitpid(pid, &status, 0);
		minishell_pid(ms);
		unlink_script();
		g_status = status;
	}
}
