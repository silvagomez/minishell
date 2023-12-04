NAME			:=	minishell
NAME_BONUS		:=	minishell_bonus

#------------------------------------------------------------------------------#
#   ART                                                                        #
#------------------------------------------------------------------------------#

define	ART

$(RED)                               -===-
$(RED)                       ....  :*=: :=*:  ....
$(RED)                     .+=--==*:       :*==--=+.
$(RED)                  .*-       -*       *-       -*.
$(RED)                  *-       :*         *:       -*
$(RED)                 .*.       =+         +=       .*.
$(RED)             .-==+*.       *-         -*       .*+==-.
$(RED)           =+:   :*        *:         :*        *:   :+=
$(RED)          =+     .*:       =+         +=       :*.     +=
$(RED)          *-      +=       =+         +=       =+      -*
$(RED)       -==*-      +=       -*         *-       =+      -*==-
$(RED)      *=. -*      :*.      =+         +=      .*:      *- .=*
$(RED)     :*.   *-      *-      -*         *-      -*      -*   .*:
$(RED)    .*:    :*.     -*       *-       -*       *-     .*:    :*.
$(RED_)     -*     -*      *-     .*:       :*.     -*      *-     *-
$(RED_)    .:*.     =*.    *-      +=       =+      -*    .*=     .*:.
$(RED_)  .*+--*.     :*:    =+      *:     :*       +=    :*:    .*--+*.
$(RED_)  -*.   :*:    :*:    +=     .:     :.     =+    :*:    :*:   .*-
$(RED_)   :*-   :*-    :*:   .*-     :*...*:     -*.   :*:    -*:   -*:
$(RED_)    -*=.  -*-    .*=   :*:   .*:   :*:   :*:   =*.    -*-  .=*-
$(RED_)       .-+  :*=.   -*:  .*:   :*...*:   :*.  :*-   .=*:  +-.
$(RED_)          :++--*+.    .++.:=.         .:=.++.    .+*--++:
$(RED_)              .-++=++-..:                 :..-++=++-.
$(RED_)                   .-++-.                   .-++-.
$(BLUE)                   By: @codelirious && @silvagomez
	
endef

export	ART

#------------------------------------------------------------------------------#
#   INGREDIENTS                                                                #
#------------------------------------------------------------------------------#

CC				:=	cc
CFLAGS			:=	-Wall -Wextra -Werror -fsanitize=address -g3
#CFLAGS			:=	-Wall -Wextra -Werror -g

INCLUDE_PATH	:=	include/
INCLUDE			:=	$(INCLUDE_PATH)minishell.h

INCLUDE_BPATH	:=	include_bonus/
INCLUDE_B		:=	$(INCLUDE_BPATH)minishell_bonus.h

LIBFT_PATH		:=	libft/
LIBFT			:=	$(LIBFT_PATH)libft.a

UNAME_OS 		:= $(shell uname -s)

ifeq ($(UNAME_OS),Linux)
	#echo -e "Linux............"
	# Linux (check for specific distributions)
  ifeq ($(shell lsb_release -si),Ubuntu)
	#echo -e "Ubuntu............"
	#readline path ubuntu
  endif
  ifeq ($(shell lsb_release -si),Fedora)
	#echo -e "Fedora............"
	#readline path fedora
  endif
endif
# macOS
ifeq ($(UNAME_OS),Darwin)
	#echo -e "Macos............"
	#readline path macos
endif

SRC_BUILTINS	:=	\
					builtins/ft_echo.c \
					builtins/ft_cd.c \
					builtins/ft_pwd.c \
					builtins/ft_unset.c \
					builtins/ft_env.c \
					builtins/ft_exit.c \
					builtins/ft_export.c \

SRC_PATH		:=	src/
SRC				:=	\
					main.c \
					quoting.c \
					redirecting.c \
					lexering0.c \
					envp.c \
					default_env.c \
					prompt.c \
					exit.c \
					parsing0.c \
					executing.c \
					executing1.c \
					dollardollar.c \
					here_doc.c \
					freeing.c \
					$(SRC_BUILTINS)

SRC				:=	$(SRC:%=$(SRC_PATH)%)

SRC_BPATH		:=	src_bonus/
SRC_BONUS		:=	\
					main_bonus.c 

SRC_BONUS		:=	$(SRC_BONUS:%=$(SRC_BPATH)%)

OBJ_PATH		:=	obj/
OBJ				:=	$(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

OBJ_BPATH		:=	obj_bonus/
OBJ_BONUS		:=	$(SRC_BONUS:$(SRC_BPATH)%.c=$(OBJ_BPATH)%.o)


W		:=	\$
R		:=	OS

#------------------------------------------------------------------------------#
#   UTENSILS                                                                   #
#------------------------------------------------------------------------------#

RM				:=	rm
RMFLAG			:=	-fr

DIR_DUP			=	mkdir -p $(@D)

#------------------------------------------------------------------------------#
#   RECIPES                                                                    #
#------------------------------------------------------------------------------#

all				:	$(NAME)

$(NAME)			:	$(OBJ) $(LIBFT)
					$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
					@echo -e "$(MAGENTA)Files $(NAME)$(GREEN) compiled!$(RESET)"
					@echo -e  "$$ART"
					@echo -e OS=$(UNAME_OS)
#					$(shell >temp echo "#!/bin/bash\nexport OS=$(UNAME_OS)\n>os_name echo $W$R")
#					$(shell chmod 777 temp)
#					$(shell ./temp)
#					$(shell unlink temp)

$(OBJ_PATH)%.o	:	$(SRC_PATH)%.c
				  	$(DIR_DUP)
					$(CC) $(CFLAGS) -I $(INCLUDE_PATH) -c $< -o $@

bonus			:	$(NAME_BONUS)

$(NAME_BONUS)	:	$(OBJ_BONUS) $(LIBFT)
					$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) -o $(NAME_BONUS)
					@echo -e "$(MAGENTA)File $(NAME_BONUS)$(GREEN) compiled!$(RESET)"

$(OBJ_BPATH)%.o	:	$(SRC_BPATH)%.c
				  	$(DIR_DUP)
					$(CC) $(CFLAGS) -I $(INCLUDE_BPATH) -c $< -o $@

$(LIBFT)		:
					make -C $(LIBFT_PATH) all

clean			:
					make -C $(LIBFT_PATH) clean
					$(RM) $(RMFLAG) $(OBJ_PATH)
					$(RM) $(RMFLAG) $(OBJ_BPATH)
					@echo -e "$(MAGENTA)Removing files... $(GREEN)done!$(RESET)"

fclean			:	clean
					make -C $(LIBFT_PATH) fclean
					$(RM) $(RMFLAG) $(NAME)
					$(RM) $(RMFLAG) $(NAME_BONUS)
					@echo -e "$(MAGENTA)Removing $(NAME) $(GREEN)done!$(RESET)"

re				:	fclean all

norm			:
					norminette $(LIBFT_PATH) $(SRC_PATH) $(INCLUDE_PATH)

run				:	re
					clear && ./$(NAME)

#------------------------------------------------------------------------------#
#   SPEC                                                                       #
#------------------------------------------------------------------------------#

.PHONY			:	all clean fclean re bonus

#------------------------------------------------------------------------------#
#   COLORS                                                                     #
#------------------------------------------------------------------------------#

RESET			:=	\033[0m
RED_			:=	\033[31m
RED				:=	\033[91m
GREEN			:=	\033[92m
YELLOW			:=	\033[93m
BLUE			:=	\033[94m
MAGENTA			:=	\033[95m
CYAN			:=	\033[96m
WHITE			:=	\033[97m

#********************************************************************* END ****#
