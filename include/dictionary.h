
#ifndef DICTIONARY_H
# define DICTIONARY_H

# define WAIT 1

// BUILTIN
# define EXPORT	1
# define UNSET	2

// SIGNALS
# define SIGDEF 1
# define SIGEXE 2
# define SIGFD	3
# define SIGHD	4

//ERRORS MSN

# define ERR_IARG	"MiniShell ERR: Invalid arguments"
# define ERR_ENVK	"MiniShell ERR: Env does not exist"
# define ERR_ONFD	"MiniShell ERR: Error opening fd"
# define ERR_EXEC	"MiniShell ERR: Execve failed"
# define ERR_UNQT	"MiniShell ERR: Unclosed quotes"
# define ERR_CNPP	"MiniShell ERR: Continuous pipes"
# define ERR_INPP	"MiniShell ERR: Syntax error near unexpected token `|'"
# define ERR_CDER	"MiniShell ERR: cd"
# define ERR_CDHM	"MiniShell ERR: cd: HOME not set"
# define ERR_CDOP	"MiniShell ERR: cd: OLWPWD not set"
# define ERR_PATH	"MiniShell ERR: No such file or directory"

//ERRORS NUM
# define ERR_DEF	1

// FILES BEHIND SCENE
# define PID_BUFFER		".temp_pid"
# define OS_NAME		".os_name"
# define SCRIPT_PID		".script_pid"

//COLOR
# define BLK		"\001\033[30m\002"
# define RED		"\001\033[31m\002"
# define GRN		"\001\033[32m\002"
# define YEL		"\001\033[33m\002"
# define BLU		"\001\033[34m\002"
# define MAG		"\001\033[35m\002"
# define CYN		"\001\033[36m\002"
# define WHT		"\001\033[37m\002"
# define RST		"\001\033[0m\002"

//HIGH COLOR
# define HBLK	"\001\033[90m\002"
# define HRED	"\001\033[91m\002"
# define HGRN	"\001\033[92m\002"
# define HYEL	"\001\033[93m\002"
# define HBLU	"\001\033[94m\002"
# define HMAG	"\001\033[95m\002"
# define HCYN	"\001\033[96m\002"
# define HWHT	"\001\033[97m\002"

#endif
