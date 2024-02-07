
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
 */
void	signal_default(int signal)
{
	if (signal == SIGINT)
	{
		/*
		 * This line uses the ioctl system call to simulate typing the newline 
		character (\n) into the standard input
		*/
		ioctl(STDIN_FILENO, TIOCSTI, "\n");
		/*
		 * This is used to replace or clean the line with empty string, this 
		 * allows us to control the case of breaking the signal and keyboard.
		 * */
		rl_replace_line("", 0);
		/*
		 * Puts the cursor in a new line.
		 */
		rl_on_new_line();
		rl_redisplay();
	}
	/*
	 * This case works but not 100%
	 */
	else if (signal == SIGQUIT)
	{
		//ft_putstr_fd("\nDo nothing | Quit", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

//update g_status;
void	signal_execute(int signal)
{
	if (signal == SIGINT)
	{
		ft_putendl_fd("\nKill process", 1);
	}
	else if (signal == SIGQUIT)
	{
		ft_putendl_fd("Quit: 3", 2);
	}
}

void	signal_hd(int signal)
{
	(void) signal;
	write(1, "SALIMOS POR HD\n", 16);
	//exit (0);
}

void	set_signal_action(int action)
{
	struct sigaction	sig_act;


	ft_bzero(&sig_act, sizeof(sig_act));
	sig_act.sa_flags = SA_RESTART;
	if (action == SIGDEF)
	{
		sig_act.sa_handler = signal_default;
		sigaction(SIGINT, &sig_act, NULL);
		sig_act.sa_handler = SIG_IGN;
		sigaction(SIGQUIT, &sig_act, NULL);
	}
	else if (action == SIGEXE)
	{
		sig_act.sa_handler = signal_execute;
		sigaction(SIGINT, &sig_act, NULL);
		sigaction(SIGQUIT, &sig_act, NULL);
	}
	else if (action == SIGHD)
	{
		sig_act.sa_handler = signal_hd;
		sigaction(SIGINT, &sig_act, NULL);
		sigaction(SIGQUIT, &sig_act, NULL);
	}

}
