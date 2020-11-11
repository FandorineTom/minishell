# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/05/13 18:05:17 by snorthmo          #+#    #+#              #
#    Updated: 2020/10/17 21:58:14 by snorthmo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c ft_memchr.c \
	ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c ft_strrchr.c \
	ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
	ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c ft_calloc.c \
	ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c \
	ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c\
	get_next_line.c get_next_line_utils.c ft_putchar.c ft_putendl.c
SRC_B = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c \
	ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c \
	ft_strcat_bonus.c ft_strcmp_bonus.c ft_strcpy_bonus.c ft_strncat_bonus.c \
	ft_strncpy_bonus.c ft_strnlen_bonus.c ft_strstr_bonus.c \
	ft_strtrimwhole_bonus.c 
OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)
FLAGS = -Wall -Werror -Wextra

.PHONY: all bonus so clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_B)
	@ar rc $(NAME) $(OBJ) $(OBJ_B)
	@ranlib $(NAME)
	@echo "The libft library created"

bonus: $(OBJ) $(OBJ_B)
	@ar rc $(NAME) $(OBJ) $(OBJ_B)
	@ranlib $(NAME)

%.o: %.c 
	@gcc -c $< -o ${<:.c=.o} 

clean:
	@/bin/rm -f $(OBJ) $(OBJ_B)

fclean: clean
	@/bin/rm -f $(NAME) 

re: fclean all
