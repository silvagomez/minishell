
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

// FILES BEHIND SCENE
# define PID_BUFFER		".temp_pid"
# define OS_NAME		".os_name"
# define SCRIPT_PID		".script_pid"

//COLOR
# define BLK		"\033[30m"
# define RED		"\033[31m"
# define GRN		"\033[32m"
# define YEL		"\033[33m"
# define BLU		"\033[34m"
# define MAG		"\033[35m"
# define CYN		"\033[36m"
# define WHT		"\033[37m"
# define RST		"\033[0m"

//HIGH COLOR
# define HBLK	"\033[90m"
# define HRED	"\033[91m"
# define HGRN	"\033[92m"
# define HYEL	"\033[93m"
# define HBLU	"\033[94m"
# define HMAG	"\033[95m"
# define HCYN	"\033[96m"
# define HWHT	"\033[97m"

#endif
