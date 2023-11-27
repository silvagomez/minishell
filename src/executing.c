
#include "minishell.h"

static const char	*g_builtin[7] = {"echo", "cd", "pwd", "export", "unset", \
	"env", "exit"};

int is_builtin(char *arg)
{
    int i;

    i = -1;
    while(++i < 7)
    {
        if (!ft_strncmp(arg, g_builtin[i], ft_strlen(arg) + 1))
            return (1);
    }
    return (0);
}

void	execute_builtin(t_ms *ms, t_lexer_token *ltoken)
{
	(void)ms;
	if (!ft_strncmp(ltoken->arg, "echo", ft_strlen(ltoken->arg) + 1))
		printf("BUILTIN ECHO SOLICITADO.\n");
		//ft_echo();
	if (!ft_strncmp(ltoken->arg, "cd", ft_strlen(ltoken->arg) + 1))
		printf("BUILTIN CD SOLICITADO.\n");
		//ft_cd(ms);
	if (!ft_strncmp(ltoken->arg, "pwd", ft_strlen(ltoken->arg) + 1))
		printf("BUILTIN PWDT SOLICITADO.\n");
		//ft_pwd(ms);
	if (!ft_strncmp(ltoken->arg, "export", ft_strlen(ltoken->arg) + 1))
		printf("BUILTIN EXPORT SOLICITADO.\n");
		//ft_export(ms, ltoken->next->arg);
	if (!ft_strncmp(ltoken->arg, "unset", ft_strlen(ltoken->arg) + 1))
		printf("BUILTIN UNSET SOLICITADO.\n");
		//ft_unset(ms, ltoken->next->arg);
	if (!ft_strncmp(ltoken->arg, "env", ft_strlen(ltoken->arg) + 1))
		printf("BUILTIN ENV SOLICITADO.\n");
		//ft_env(ms);
	if (!ft_strncmp(ltoken->arg, "exit", ft_strlen(ltoken->arg) + 1))
		printf("BUILTIN EXIT SOLICITADO.\n");
		//ft_exit();
}

void	execute_program(t_ms *ms)
{
    int		pid;

	pid = fork();
	if (!pid)
	{
		if (execve(ms->cmd_array[0], ms->cmd_array, ms->envp) == -1)
			printf(HRED"¡EJECUCIÓN FALLIDA!"RST"\n");
		exit(0);
	}
	else
	{
		waitpid(pid, NULL, WNOHANG);
	}
}

void	create_array(t_ms *ms, t_lexer_token *ltoken)
{
    t_lexer_token	*ltmp;
    int				i;

	ms->cmd_array = malloc(sizeof(char *) * (lexer_token_count(ltoken) + 1));
	ltmp = ltoken;
	i = 0;
	while (ltmp)
	{
		ms->cmd_array[i] = ltmp->arg;
		i++;
		ltmp = ltmp->next;
	}
	ms->cmd_array[i] = 0;
}

void execute_token(t_ms *ms, t_parser_token *token)
{
    if (is_builtin(token->lxr_list->arg))
    {
        printf("\n\n%s IS A BUILTIN\n\n", token->lxr_list->arg);
        //execute_builtin(ms, token->lxr_list);
    }
    else
    {
        printf("\n\n%s IS NOT A BUILTIN\n\n", token->lxr_list->arg);
        create_array(ms, token->lxr_list);
        execute_program(ms);
		free(ms->cmd_array);
    }
}
