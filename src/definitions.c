
#include "minishell.h"

const char	*g_type[12] = {"command", "flag", "pipe", "builtin", \
	"redirection1", "redirection2", "redirection3", "expansion", "substitution", \
	"variable_assign", "arithmetic", "forbidden"};

const char	*g_builtin[7] = {"echo", "cd", "pwd", "export", "unset", "env", \
	"exit"};
