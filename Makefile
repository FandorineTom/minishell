# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/13 20:15:44 by scopycat          #+#    #+#              #
#    Updated: 2021/01/09 17:37:56 by snorthmo         ###   ########.fr        #
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
parse_quotes.c\
pars_command.c\
pars_dollar.c\
pars_env.c\
pars_escaping.c\
pars_lib_utils.c\
pars_pipes.c\
pars_redirect.c \
pars_structs_utils.c\
pars_tockens.c\
redirect.c\
sys_mistakes_utils.c\
cmd_echo.c\
cmd_start.c\
cmd_cd.c\
cmd_pwd.c\
cmd_env.c\
cmd_export.c\
cmd_unset.c\
cmd_exit.c\
signal.c\
minishell.c\
fd_utils.c\
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
