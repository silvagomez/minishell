
#include "minishell.h"

/* 
 * ctrl-C	displays a new prompt on a new line.
 * 			sends SIGINT to interrupt.
 *
 * ctrl-D	exits the shell.
 * 			EOF.
 *
 * ctrl-\	does nothing.
 * 			sends SIGQUIT to kill them.
 * 
 * In Bash, pressing Ctrl-\ sends the SIGQUIT signal to the currently 
 * running process. This signal is similar to Ctrl-C (SIGINT), 
 * but it also produces a core dump of the process. 
 * It's a way to gracefully exit a process and obtain debugging information 
 * in case the process is misbehaving.
 *
 * SIG_IGN Request that signal to be ignored.
 */

/*
 * Interactive mode output bash$ ^C
 * return prompt
 *
 * Non interactive mode output bash$ ^C
 * interrupt process return prompt
 *
 * rl_replace_line:
 * 		This is used to replace or clean the line with empty string, this 
 * 		allows us to control the case of breaking the signal and keyboard.
 * ioctl:
 * 		This line uses the ioctl system call to simulate typing the newline 
 * 		character (\n) into the standard input
 * rl_on_new_line:
 * 		Puts the cursor in a new line.
 */
void	signal_default(int signal)
{
	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		g_status = 1;
	}
}

//update g_status;
void	signal_execute(int signal)
{
	if (signal == SIGINT)
		ft_putendl_fd("", 1);
	else if (signal == SIGQUIT)
		ft_putendl_fd("Quit: 3", 1);
}

void	signal_hd(int signal)
{
	if (signal == SIGINT)
	{
		close(0);
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		rl_on_new_line();
		g_status = 1;
	}
}

void	set_signal_action(int action)
{
	struct sigaction	sig_act;
	struct sigaction	sig_act_quit;

	ft_bzero(&sig_act, sizeof(sig_act));
	ft_bzero(&sig_act_quit, sizeof(sig_act_quit));
	sig_act.sa_flags = SA_RESTART;
	sig_act_quit.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig_act_quit, NULL);
	if (action == SIGDEF)
		sig_act.sa_handler = signal_default;
	else if (action == SIGHD)
		sig_act.sa_handler = signal_hd;
	else if (action == SIGEXE)
	{
		sig_act.sa_handler = signal_execute;
		sigaction(SIGQUIT, &sig_act, NULL);
	}
	sigaction(SIGINT, &sig_act, NULL);
}
