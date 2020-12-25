# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/13 20:15:44 by scopycat          #+#    #+#              #
#    Updated: 2020/12/23 18:49:58 by scopycat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #



FLAG = -g -Wall -Wextra -Werror

NAME = libminishell.a

FUNC = main.c\
check_mistakes.c\
free_struct.c\
ft_itoa.c\
get_next_line.c\
get_next_line_utils.c\
inits.c\
parser.c\
parse_quotes.c

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
