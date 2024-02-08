#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define HRED "\x1B[31m"
#define RST "\x1B[0m"

int main(int ac, char **av, char **envp) 
{
	(void) ac;
	(void) av;
	(void) envp;
    char **cmd_array;
		
	cmd_array = malloc(sizeof(char *) * 3);

	//cmd_array[0] = "/usr/bin/which";
	cmd_array[0] = "/usr/bin/pgrep";
	cmd_array[1] = "minishell";
	//cmd_array[1] = "ls";
	cmd_array[2] = 0;

    if (execve(cmd_array[0], cmd_array, NULL) == -1) {
        perror(HRED"¡EJECUCIÓN FALLIDA!"RST);
        exit(EXIT_FAILURE);
    }

    return 0;
}
