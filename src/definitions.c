
#include "minishell.h"

static const char	*g_type[12] = {"program", "flag", "pipe", "builtin", \
	"redirection1", "redirection2", "redirection3", "expansion", \
	"substitution", "variable_assign", "arithmetic", "forbidden"};

static const char	*g_builtin[7] = {"echo", "cd", "pwd", "export", "unset", \
	"env", "exit"};

static const char	*g_spchar[] = {";", "*", "?", "!", "`", "^", "#", "&", \
	"&&", "||", "(", ")", "[", "]", "{", "}", "<<<", ">>>" };
