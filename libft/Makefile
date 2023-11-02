# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edejimen <edejimen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/02 14:20:21 by edejimen          #+#    #+#              #
#    Updated: 2023/11/02 12:47:17 by edejimen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a

CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror
AR				=	ar
ARFLAGS 		=	rcs
RM				=	rm -rf


SRC_DIR			:=	src/
SRC				:=	ft_isalnum ft_isprint ft_memcmp ft_putchar_fd\
					ft_split ft_strlcat ft_strncmp ft_substr\
					ft_atoi ft_isalpha ft_itoa ft_memcpy\
					ft_putendl_fd ft_strchr ft_strlcpy ft_strnstr\
					ft_tolower ft_bzero ft_isascii ft_striteri\
					ft_memmove ft_putnbr_fd ft_strdup ft_strlen\
					ft_strrchr ft_toupper ft_calloc ft_isdigit\
					ft_memchr ft_memset ft_putstr_fd ft_strjoin\
					ft_strmapi ft_strtrim get_next_line ft_printf\
					ft_uitoa ft_print_num ft_print_hex ft_print_ptr\
					ft_print_str ft_print_char\
					ft_lstadd_back ft_lstadd_front ft_lstnew\
					ft_lstsize ft_lstlast ft_lstdelone ft_lstclear\
					ft_lstiter ft_lstmap
SRCS 			:=	$(SRC_DIR)$(addsuffix .c, $(SRC))
					
OBJ_DIR			:=	obj/
OBJS			:=	$(addsuffix .o, $(addprefix $(OBJ_DIR), $(SRC)))

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c
					$(CC) $(CFLAGS) -I include/ -c $< -o $@

all:				$(NAME)

$(NAME):			$(OBJ_DIR) $(OBJS)
					$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(OBJ_DIR):
					mkdir -p $(OBJ_DIR)

clean:
					$(RM) $(OBJ_DIR)

fclean:				clean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re