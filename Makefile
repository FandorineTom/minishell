# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scopycat <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/13 20:15:44 by scopycat          #+#    #+#              #
#    Updated: 2020/11/08 22:45:59 by scopycat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



FLAG = -g -Wall -Wextra -Werror

NAME = libminishell.a

FUNC = main.c\
get_next_line.c\
get_next_line_utils.c\
inits.c\
parser.c

OBJ = $(FUNC:.c=.o)

O_BONUS = $(BONUS:.c=.o)

HEADER = minishell.h

.PHONY: all clean fclean re bonus

all: $(NAME)

%.o: %.c $(HEADER)
	gcc $(FLAG) -c $< -o $@

$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)
	gcc $(FUNC) $(FLAG) -o minishell 
	ranlib $(NAME)

bonus: $(OBJ) $(O_BONUS)
	ar -rc $(NAME) $(OBJ) $(O_BONUS)


clean:
	rm -f $(OBJ) $(O_BONUS)

fclean: clean
	rm -f $(NAME)

re: fclean all
