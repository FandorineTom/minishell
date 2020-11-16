# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/11 16:45:52 by snorthmo          #+#    #+#              #
#    Updated: 2020/11/15 14:18:49 by snorthmo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libminishell.a

CC = gcc
FLAGS = -g -Wall -Wextra -Werror
LIBFT = libft/libft.a
MAIN = main.c
SRC = cmd_echo.c\
		cmd_start.c\
		cmd_cd.c\
		main.c
OBJ = $(SRC:.c=.o)
RM = rm -rf
HEADER = minishell.h

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)
	$(CC) $(FLAGS) $(SRC) $(LIBFT) -o minishell

%.o: %.c $(HEADER)
	$(CC) $(FLAG) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C libft

clean:
		$(MAKE) clean -C ./libft
		$(RM) $(OBJ)

fclean: clean
		$(MAKE) fclean -C ./libft
		$(RM) $(NAME)
		$(RM) minishell

re: fclean $(NAME)