# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/13 20:15:44 by scopycat          #+#    #+#              #
#    Updated: 2020/11/29 16:38:01 by scopycat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAG = -g -Wall -Wextra -Werror

NAME = libminishell.a

FUNC = main.c\
get_next_line.c\
get_next_line_utils.c\
inits.c\
parser.c\
cmd_echo.c\
cmd_start.c\
cmd_cd.c\
cmd_pwd.c\
error.c

OBJ = $(FUNC:.c=.o)

O_BONUS = $(BONUS:.c=.o)

HEADER = minishell.h

LIBFT = libft/libft.a

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	ar -rc $(NAME) $(OBJ)
	gcc $(FUNC) $(LIBFT) $(FLAG) -o minishell 
	ranlib $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAG) -c $< -o $@

$(LIBFT):
	@$(MAKE) -C libft

bonus: $(OBJ) $(O_BONUS)
	ar -rc $(NAME) $(OBJ) $(O_BONUS)


clean:
	$(MAKE) clean -C ./libft
	rm -f $(OBJ) $(O_BONUS)

fclean: clean
	$(MAKE) fclean -C ./libft
	rm -f $(NAME)
	rm -f minishell

re: fclean all