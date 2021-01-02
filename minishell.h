/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:50:14 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/02 16:20:08 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <sys/errno.h>
# include <string.h>
# include "./headers/get_next_line.h"
# include "libft/libft.h"

typedef struct		s_pipe
{
	struct s_pipe	*next;
	int				fd_read;
	int				fd_write;
}					t_pipe;

typedef struct		s_flag
{
	struct s_flag	*next;
	char			*flag;
	size_t			no_flag; // изначально 1, если флаги не найдены, то обнуляется
}					t_flag;

typedef struct		s_arg
{
	struct s_arg	*next;
	struct s_arg	*previous;
	char			*arg;
	char			*path; // вспомнить, зачем это
	// t_pipe			*pipes; // тут это скорее всего не нужно
	size_t			wildcard; // для бонуса если 0, но звездочки нет, если 1, то есть и можно вспомнить matchtomatch
	size_t			no_arg; // изначально  1, если аргументы не найдены, то обнуляется // не нужна в целом
}					t_arg;

typedef	struct		s_redir
{
	struct s_redir	*next;
	struct s_redir	*previous;
	int				fd1;
	int				fd2;
	char			*file_name;
	size_t			type_red;
	size_t			r_redir;
	size_t			l_redir;
}					t_redir;

typedef struct		s_comd
{
	struct s_comd	*next;
	struct s_comd	*previous;
	char			*cmnd;
	t_flag			*flag;
	t_arg			*arg;
	char			*env_var; // переменная для команды
	size_t			pipe_r;
	size_t			pipe_l;
	t_redir			*redir;
	size_t			no_command; // изначально 1, если команды не найдены, то обнуляется
}					t_comd;

typedef struct		s_env
{
	struct s_env	*next;
	char			*env;
	char			*meaning; 

}					t_env;


typedef struct		s_command
{
	t_comd			*comd;
	// t_arg			*arg;
	char			*env_var; // переменная, которая просто выводится (или исполняется)
	t_env			*env_def;
	size_t			error;
	size_t			quotes_op;
	// size_t			no_command; //обнуляется, если нет команды. изначально количество pipe + 1
	// size_t			no_arg; // обнуляется, если нет аргументов. изначально количество pipe + 1
	size_t			no_var; // обнуляется, если нет переменной окружения. изначально количество pipe + 1
	size_t			pipe_count;
	size_t			process[100]; // сюда пишутся переменные, которые возвращает fork
	size_t			com_ret;
}					t_command;

void				parser(char **line, t_command *com);
void				pars_pipes(char *line, t_command *com);
void				pars_tockens(char **line, t_command *com);
void				pars_single_quotes(char **line, t_command *com);
void				pars_double_quotes(char **line, t_command *com);
void				pars_esc_nq(char **line, t_command *com);
void				check_result(t_command *com);
void    			check_mistakes(char **line_true, t_command *com);
void				check_mistakes_quotes(char **line);
void				check_mistakes_inside(char **line, size_t *i, char **line_true, t_command *com);
void				please_enter(char **line_true, size_t *i, t_command *com);
int					check_command(char **line, t_command *com);
int					check_echo_flag(char **line, t_command *com);
int 				check_which_command(char **line, t_command *com, char *command, int i);
int 				check_env_var(char **line, t_command *com);
void				change_env_var_meaning(t_command *com);
void				check_tockens(char **line, t_command *com);
void				work_comman(t_command *com);
void				init_com(t_command *com);
void				init_comd(t_command *com);
void				init_flag(t_command *com);
void				init_arg(t_command *com);
void				init_env_d(t_command *com);
void				init_env_def(t_env *env);
void				init_redirect(t_command *com);
size_t				ft_strlen_space(char *str);
size_t				ft_strlen_char(char *str, char c);
size_t				find_len_to_ss(char *line);
int					check_open_quotes(char **line, size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strchr(const char *str, int sym);
void				copy_env(char **env, t_command *com);
void				ft_envadd_back(t_env **lst, t_env *new);
void				ft_argadd_back(t_arg **lst, t_arg *new);
void				ft_comdadd_back(t_comd **lst, t_comd *new);
void				ft_redadd_back(t_redir **lst, t_redir *new);
void				free_all(t_command *com, int i); // если приходит 1 то чистится все, кроме списка переменных окружения, если 0, то чистится все
void				free_comd(t_comd *comd);
void				free_flag(t_flag *flag);
void 				free_arg(t_arg *arg);
void				free_pipe(t_pipe *pipes);
void				free_env(t_env *env_def);
int					check_flag_n(char *line, int quotes);
void 				pars_dollar(t_command *com, size_t len_str);
void				pars_escaping(t_command *com, size_t len_str);
void				pars_redirect(char **line, t_command *com);
void				pars_reverse_redirect(char **line, t_command *com);
void				activate_pipe(char **line, t_command *com);
char				*ft_itoa(int n);
void				cmd_start(t_command *com);
void	 			cmd_echo(t_command *com);
int					cmd_cd(t_command *com);
int					cmd_pwd(void);
int					cmd_env(t_command *com);
int					error_message(char *message, int exit_code);
int					cmd_export(t_command *com);
char				*detect_env_var(t_command *com);
t_env				*new_node(char *var, char *mean);
char				*find_meaning(t_command *com);
int					error_export(t_command *com);
int					cmd_unset(t_command *com);
int					cmd_exit(void);

#endif
