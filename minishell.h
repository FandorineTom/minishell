/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:50:14 by scopycat          #+#    #+#             */
/*   Updated: 2020/11/10 23:04:27 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include "get_next_line.h"

typedef struct		s_flag
{
	struct s_flar	*next;
	char			*flag;
	size_t			no_flag; // изначально 1, если флаги не найдены, то обнуляется
}					t_flag;

typedef struct		s_comd
{
	struct s_comd	*next;
	char			*cmnd;
	t_flag			*flag;
	char			*env_var; // переменная для команды
	size_t			no_command; // изначально 1, если команды не найдены, то обнуляется
}					t_comd;

typedef struct	s_arg
{
	struct s_arg	*next;
	char			*arg;
	char			*path;
	size_t			wildcard; // для бонуса если 0, но звездочки нет, если 1, то есть и можно вспомнить matchtomatch
	size_t			no_arg; // изначально  1, если аргументы не найдены, то обнуляется
}					t_arg;

typedef struct		s_command
{
	t_comd			*comd;
	t_arg			*arg;
	char			*env_var; // переменная, которая просто выводится (или исполняется)
	size_t			no_command; //обнуляется, если нет команды. изначально количество pipe + 1
	size_t			no_arg; // обнуляется, если нет аргументов. изначально количество pipe + 1
	size_t			no_var; // обнуляется, если нет переменной окружения. изначально количество pipe + 1
	size_t			pipe_count;
	size_t			process[100]; // сюда пишутся переменные, которые возвращает fork
}					t_command;

int					main(void);
void				parser(char *line, t_command *com);
void				pars_pipes(char *line, t_command *com);
void				pars_commands(char *line, t_command *com);
void				work_comman(t_command *com);
void				free_all(t_command *com);
void				init_com(t_command *com);
void				init_comd(t_command *com);
void				init_flag(t_command *com);
void				init_arg(t_command *com);
char				**ft_split(char const *s, char c);

#endif
