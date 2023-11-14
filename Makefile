
NAME			:=	minishell
NAME_BONUS		:=	minishell_bonus

#------------------------------------------------------------------------------#
#   INGREDIENTS                                                                #
#------------------------------------------------------------------------------#

CC				:=	cc
#CFLAGS			:=	-Wall -Wextra -Werror -fsanitize=address -g3
CFLAGS			:=	-Wall -Wextra -Werror -g

INCLUDE_PATH	:=	include/
INCLUDE			:=	$(INCLUDE_PATH)minishell.h

INCLUDE_BPATH	:=	include_bonus/
INCLUDE_B		:=	$(INCLUDE_BPATH)minishell_bonus.h

LIBFT_PATH		:=	libft/
LIBFT			:=	$(LIBFT_PATH)libft.a

SRC_PATH		:=	src/
SRC				:=	\
					main.c \
					quoting.c \
					redirecting.c \
					parsing0.c

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
					$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -o $(NAME)
					@echo -e "$(MAGENTA)File $(NAME)$(GREEN) compiled!$(WHITE)"

$(OBJ_PATH)%.o	:	$(SRC_PATH)%.c
				  	$(DIR_DUP)
					$(CC) $(CFLAGS) -I $(INCLUDE_PATH) -c $< -o $@

bonus			:	$(NAME_BONUS)

$(NAME_BONUS)	:	$(OBJ_BONUS) $(LIBFT)
					$(CC) $(CFLAGS) $(OBJ_BONUS) $(LIBFT) -o $(NAME_BONUS)
					@echo -e "$(MAGENTA)File $(NAME_BONUS)$(GREEN) compiled!$(WHITE)"

$(OBJ_BPATH)%.o	:	$(SRC_BPATH)%.c
				  	$(DIR_DUP)
					$(CC) $(CFLAGS) -I $(INCLUDE_BPATH) -c $< -o $@

$(LIBFT)		:
					make -C $(LIBFT_PATH) all

clean			:
					make -C $(LIBFT_PATH) clean
					$(RM) $(RMFLAG) $(OBJ_PATH)
					$(RM) $(RMFLAG) $(OBJ_BPATH)
					@echo -e "$(MAGENTA)Removing files... $(GREEN)done!$(WHITE)"

fclean			:	clean
					make -C $(LIBFT_PATH) fclean
					$(RM) $(RMFLAG) $(NAME)
					$(RM) $(RMFLAG) $(NAME_BONUS)
					@echo -e "$(MAGENTA)Removing $(NAME) $(GREEN)done!$(WHITE)"

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

GREEN			:=	\033[92m
BLUE			:=	\033[94m
MAGENTA			:=	\033[95m
WHITE			:=	\033[97m

#********************************************************************* END ****#
