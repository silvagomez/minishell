

#include "minishell.h"

/* 
 * ctrl-C	displays a new prompt on a new line.
 * 			sends SIGINT to interrup.
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
 * SIG_IGN Request that signal be ignored.
 */

/*
 * Interactive mode output bash$ ^C
 * return prompt
 *
 * Non interactive mode oput bash$ ^C
 * interrupt process return prompt
 */
void	signal_interrupt(int sig)
{
	//SIGINT ID 2
	if (sig == 2)
	{
		printf("Process killed | Prompt\n");
		print_prompt();
	}
		//interrupt
		//print prompt
}

/*
 * Output bash: exit
 */
/*
void	signal_exit(int sig)
{
	if (sig == SIGQUIT)
		//free
		//print exit
		//exit
}
*/

/*
 * In bash with keyboard in ES ctrl + ç is ctrl-\
 * Output bash: * ^\Quit: 3
 * Output minishell: do nothing.
 */
/*
void	signal_nothing(int sig)
{
	if (sig == SIGQUIT)
		//do nothing
}
*/


void	set_signal_action(int option)
{
	struct sigaction	sact_ctrl_c;
	//struct sigaction	sact_ctrl_d;
	//struct sigaction	sact_ctrl_backslash;


	ft_bzero(&sact_ctrl_c, sizeof(sact_ctrl_c));
	//ft_bzero(&sact_ctrl_d, sizeof(sact_ctrl_d));
	//ft_bzero(&sact_ctrl_backslash, sizeof(sact_ctrl_backslash));


	sact_ctrl_c.sa_handler = signal_interrupt;
	sigaction(SIGINT, &sact_ctrl_c, NULL);
	(void)option;
	/*
	s_ms_sact_quit.sa_handler = signal_exit;
	//s_ms_sact_quit.sa_sigaction = signal_exit;
	if (sigaction(SIGQUIT, &s_ms_sact_quit, NULL) < 0)
		write(2, "Error\n", 6);

	s_ms_sact_quit.sa_handler = SIG_IGN;
	//s_ms_sact_quit.sa_sigaction = SIG_IGN;
	if (sigaction(SIGQUIT, &s_ms_sact_not, NULL) < 0)
		write(2, "Error\n", 6);

	if (option == case_1)
	{
		s_ms_sact_int.sa_handler = signal_interrupt;
	//	s_ms_sact_int.sa_sigaction = signal_interrupt;
	}
	else if (option == case_2)
	{
		s_ms_sact_int.sa_handler = signal_interrupt_2;
	//	s_ms_sact_int.sa_sigaction = signal_interrupt_2;
	}
	if (sigaction(SIGINT, &s_ms_sact_not, NULL) < 0)
	write(2, "Error\n", 6);

	*/
}
