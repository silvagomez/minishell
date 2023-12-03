
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

void	env_to_path(t_ms *ms, t_envlst *envlst)
{
	int		i;
	char	*str;
	char	*tmp;

	while (envlst)
	{
		if (ft_strncmp("PATH", envlst->name, 5) == 0)
		{
			str = ft_strdup(envlst->content);
			break ;
		}
		else
			envlst = envlst->next;
	}
	ms->pathlist = ft_split (str, ':');
	i = 0;
	while (ms->pathlist[i])
	{
		tmp = ms->pathlist[i];
		ms->pathlist[i] = ft_strjoin(tmp, "/");
		free(tmp);
		i++;
	}
	free(str);
}

int	get_command(t_ms *ms, t_parser_token *ptoken)
{
	int	i;

	i = 0;
	while (ms->pathlist[i])
	{
		ms->cmd = ft_strjoin(ms->pathlist[i], ptoken->lxr_list->arg);
		if (access(ms->cmd, F_OK) == 0)
			{
				free(ms->cmd_array[0]);
				ms->cmd_array[0] = ms->cmd;
				break ;
			}
		i++;
	}
	if (ms->pathlist[i] == NULL)
	{
		if (access(ptoken->lxr_list->arg, F_OK) != 0)
			ms->cmd = ptoken->lxr_list->arg;
		else
			return (0);
	}
	return (1);
}

void	execute_builtin(t_ms *ms, t_parser_token *ptoken, t_lexer_token *ltoken)
{
	(void)ms;
	if (!ft_strncmp(ltoken->arg, "echo", ft_strlen(ltoken->arg) + 1))
		ft_echo(ptoken, ltoken->next);
	if (!ft_strncmp(ltoken->arg, "cd", ft_strlen(ltoken->arg) + 1))
		ft_cd(ms, ltoken);
	if (!ft_strncmp(ltoken->arg, "pwd", ft_strlen(ltoken->arg) + 1))
		ft_pwd(ms);
	if (!ft_strncmp(ltoken->arg, "export", ft_strlen(ltoken->arg) + 1))
		execute_export(ms, ltoken);
	if (!ft_strncmp(ltoken->arg, "unset", ft_strlen(ltoken->arg) + 1))
		ft_unset(ms, ltoken->next->arg);
	if (!ft_strncmp(ltoken->arg, "env", ft_strlen(ltoken->arg) + 1))
		ft_env(ms);
	if (!ft_strncmp(ltoken->arg, "exit", ft_strlen(ltoken->arg) + 1))
		printf("BUILTIN EXIT SOLICITADO.\n");
		//ft_exit();
}

void	execute_program(t_ms *ms, t_parser_token *token)
{
    int		pid;

	pid = fork();
	if (!pid)
	{
		if (get_command(ms, token))
		{
			if(token->is_input)
				dup2(token->input_fd, STDIN_FILENO);
			if (execve(ms->cmd_array[0], ms->cmd_array, ms->envp) == -1)
				printf(HRED"¡EJECUCIÓN FALLIDA DE %s!"RST"\n", ms->cmd);
			exit(0);
		}
		else
			printf("COMANDO %s NO ENCONTRADO\n", token->lxr_list->arg);
	}
	else
	{
		waitpid(pid, NULL, 0);
		if (token->is_input)
			close (token->input_fd);
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
	static int i = 1;

	printf(HGRN"\n\n__--EXECUTION #%i--__\n"RST"\n", i++);
    if (is_builtin(token->lxr_list->arg))
    {
        //printf("\n\n%s IS A BUILTIN\n\n", token->lxr_list->arg);
        execute_builtin(ms, token, token->lxr_list);
    }
    else
    {
        //printf("\n\n%s IS NOT A BUILTIN\n\n", token->lxr_list->arg);
        create_array(ms, token->lxr_list);
        execute_program(ms, token);
		free(ms->cmd_array);
    }
}
