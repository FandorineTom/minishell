/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:50:14 by scopycat          #+#    #+#             */
/*   Updated: 2020/11/08 23:00:43 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "./headers/get_next_line.h"

typedef struct	s_flag
{
	char		*flag;
	char		*next;
}				t_flag;

typedef struct	s_comd
{
	char		*cmnd;
	t_flag		*flag;
	char		*env_var; // переменная для команды
	char		*next;
}				t_comd;

typedef struct	s_arg
{
	char		*arg;
	size_t		wildcard; // для бонуса если 0, но звездочки нет, если 1, то есть и можно вспомнить matchtomatch
	char		*next;
}				t_arg;

typedef struct	s_command
{
	t_comd		*comd;
	t_arg		*arg;
	char		*env_var; // переменная, которая просто выводится (или исполняется)
	size_t		no_command; //обнуляется, если нет команды
	size_t		no_arg; // обнуляется, если нет аргументов
	size_t		no_var; // обнуляется, если нет переменной окружения
	size_t		pipe_count;
	size_t		process[1028]; // не помню для чего сделала, но кажется нужно
}				t_command;

void			parser(char *line, t_command *com);
void			pars_pipes(char *line, t_command *com);
void			work_comman(t_command *com);
void			free_all(t_command *com);
void			init(t_command *com);

#endif
