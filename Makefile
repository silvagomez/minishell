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
$(RESET)	
endef

export	ART

#------------------------------------------------------------------------------#
#   INGREDIENTS                                                                #
#------------------------------------------------------------------------------#

CC				:=	cc
CFLAGS			:=	-Wall -Wextra -Werror -g3 #-fsanitize=address
#CFLAGS			:=	-Wall -Wextra -Werror -g

INCLUDE_PATH	:=	include/
INCLUDE			:=	$(INCLUDE_PATH)minishell.h

INCLUDE_BPATH	:=	include_bonus/
INCLUDE_B		:=	$(INCLUDE_BPATH)minishell_bonus.h

LIBFT_PATH		:=	libft/
LIBFT			:=	$(LIBFT_PATH)libft.a

UNAME_OS 		:= $(shell uname -s)

ifeq ($(UNAME_OS),Linux)
RLFLAG			:= -lreadline -L/usr/include/readline
RLINC			:= -I/usr/include/readline
else ifeq ($(UNAME_OS),Darwin)
RLFLAG			:= -lreadline -L/Users/$(USER)/.brew/opt/readline/lib
RLINC			:= -I/Users/$(USER)/.brew/opt/readline/include
endif

SRC_BUILTINS	:=	\
					builtins/ft_echo.c \
					builtins/ft_cd.c \
					builtins/ft_pwd.c \
					builtins/ft_unset.c \
					builtins/ft_env.c \
					builtins/ft_exit.c \
					builtins/ft_export.c \
					builtins/ft_declare.c \
					builtins/export_utils0.c \
					builtins/export_utils1.c \
					builtins/cd_utils0.c \

SRC_PATH		:=	src/
SRC				:=	\
					main.c \
					handling0.c \
					quoting0.c \
					redirecting0.c \
					redirecting1.c \
					lexering0.c \
					lexering1.c \
					lexering2.c \
					lexering3.c \
					lexering4.c \
					lexering5.c \
					lexering6.c \
					envp0.c \
					envp1.c \
					envp2.c \
					setting_defaults0.c \
					prompting0.c \
					freeing_exit.c \
					parsing0.c \
					parsing1.c \
					parsing2.c \
					parsing3.c \
					executing0.c \
					executing1.c \
					executing2.c \
					executing3.c \
					executing4.c \
					executing5.c \
					executing6.c \
					executing7.c \
					piding0.c \
					dollardollar0.c \
					here_doc0.c \
					here_doc1.c \
					here_doc2.c \
					freeing0.c \
					signaling0.c \
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
					$(CC) $(CFLAGS) $(OBJ) $(LIBFT) $(RLFLAG) -o $(NAME)
					@echo -e "$(MAGENTA)Files $(NAME)$(GREEN) compiled!$(RESET)"
					@echo -e  "$$ART"
#					@echo -e OS=$(UNAME_OS)

$(OBJ_PATH)%.o	:	$(SRC_PATH)%.c
				  	$(DIR_DUP)
					$(CC) $(CFLAGS) -I $(INCLUDE_PATH) $(RLINC) -c $< -o $@

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
