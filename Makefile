# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/13 20:15:44 by scopycat          #+#    #+#              #
#    Updated: 2021/01/24 15:29:07 by snorthmo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FLAG = -g -Wall -Wextra -Werror

NAME = libminishell.a

FUNC = main.c\
parser_srsc/check_mistakes.c\
parser_srsc/free_struct.c\
parser_srsc/free_struct_2.c\
parser_srsc/ft_itoa.c\
parser_srsc/get_next_line.c\
parser_srsc/get_next_line_utils.c\
parser_srsc/inits.c\
parser_srsc/inits_2.c\
parser_srsc/parser.c\
parser_srsc/parse_quotes.c\
parser_srsc/pars_command.c\
parser_srsc/pars_dollar.c\
parser_srsc/pars_env.c\
parser_srsc/pars_escaping.c\
parser_srsc/pars_lib_utils.c\
parser_srsc/pars_pipes.c\
parser_srsc/pars_redirect.c \
parser_srsc/pars_structs_utils.c\
parser_srsc/pars_tockens.c\
parser_srsc/pars_tocken_utils.c\
parser_srsc/redirect.c\
parser_srsc/sys_mistakes_utils.c\
cmd_srcs/cmd_echo.c\
cmd_srcs/cmd_start.c\
cmd_srcs/cmd_cd.c\
cmd_srcs/cmd_pwd.c\
cmd_srcs/cmd_env.c\
cmd_srcs/cmd_export.c\
cmd_srcs/cmd_export_noargs.c\
cmd_srcs/cmd_unset.c\
cmd_srcs/cmd_exit.c\
cmd_srcs/signal.c\
cmd_srcs/minishell.c\
cmd_srcs/fd_utils.c\
cmd_srcs/cmd_utils.c\
cmd_srcs/cmd_cd_utils.c\
cmd_srcs/error.c

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
