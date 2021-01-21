/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:50:14 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/21 17:24:06 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <errno.h>
# include <limits.h>
# include <string.h>
# include <dirent.h>
# include <fcntl.h>
# include <signal.h>
# include "./headers/get_next_line.h"
# include "libft/libft.h"

int					g_tmp_fd[2];
int					g_fdin;
int					g_fdout;
int					g_c_flag;
int					g_b_flag;

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
	size_t			no_flag;
}					t_flag;

typedef struct		s_arg
{
	struct s_arg	*next;
	struct s_arg	*previous;
	char			*arg;
	char			*path;
	size_t			no_arg;
}					t_arg;

typedef	struct		s_redir
{
	struct s_redir	*next;
	struct s_redir	*previous;
	int				fd1; // вот это вроде тоже не используется, да? 
	int				fd2;
	char			*file_name;
	size_t			type_red;
	size_t			r_redir;
	size_t			l_redir; // не нужен, удалить
}					t_redir;

typedef struct		s_comd
{
	struct s_comd	*next;
	struct s_comd	*previous;
	char			*cmnd;
	t_flag			*flag;
	t_arg			*arg;
	char			*env_var;
	size_t			pipe_r;
	size_t			pipe_l;
	t_redir			*redir;
	size_t			no_command;
	size_t			error_redir;
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
	char			*env_var;
	t_env			*env_def;
	size_t			error;
	size_t			quotes_op;
	size_t			no_var;
	size_t			pipe_count;
	size_t			process[100];
	size_t			com_ret;
}					t_command;

void				parser(char **line, t_command *com);
void				pars_tockens(char **line, t_command *com);
void				pars_tockens_2(t_command *com, char **line, t_arg *new);
void				pars_single_quotes(char **line, t_command *com);
void				pars_double_quotes(char **line, t_command *com);
void				double_quotes_utils(t_command *com, char **line,\
						size_t len);
void				pars_esc_nq(char **line, t_command *com);
void				check_result(t_command *com);
void				check_result_utils(t_command *com, t_arg *new);
void				check_mistakes(char **line_true, t_command *com);
void				check_mistakes_quotes(char **line);
void				check_mistakes_inside(char **line, size_t *i, \
						char **line_true, t_command *com);
void				check_line_mistakes(char **line, size_t *i, \
						char **line_true, t_command *com);
void				check_multyline(char **line, size_t *i, \
					char **line_true, t_command *com);
size_t				skip_sp(char *line);
void				rewrite_line(char **line_true, char **line);
void				please_enter(char **line_true, size_t *i, t_command *com);
int					check_command(char **line, t_command *com);
int					check_echo_flag(char **line, t_command *com);
int					check_which_command(char **line, t_command *com, \
						char *command, int i);
void				define_quotes(int *quotes, char *line, int i);
int					check_env_var(char **line, t_command *com);
void				change_env_var_meaning(t_command *com);
void				no_such_env(t_command *com, size_t len);
void				change_env(t_command *com);
void				check_tockens(char **line, t_command *com);
void				check_tockens_ss(char **line, t_command *com);
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
size_t				ft_strlen_char_slash(char *str, char c);
size_t				find_len_to_ss(char *line);
size_t				find_len_tockens(char **line);
size_t				find_len_tockens_2(size_t len, char **line);
int					check_open_quotes(char **line, size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strchr(const char *str, int sym);
void				copy_env(char **env, t_command *com);
void				ft_envadd_back(t_env **lst, t_env *new);
void				ft_argadd_back(t_arg **lst, t_arg *new);
void				ft_comdadd_back(t_comd **lst, t_comd *new);
void				ft_redadd_back(t_redir **lst, t_redir *new);
void				ft_argdel_list(t_arg **old);
void				free_all(t_command *com, int i);
void				free_comd(t_comd *comd);
void				free_flag(t_flag *flag);
void				free_arg(t_arg *arg);
void				free_redirect(t_redir *redir);
void				free_pipe(t_pipe *pipes);
void				free_env(t_env *env_def);
int					check_flag_n(char *line, int quotes);
void				pars_dollar(t_command *com, size_t len_str);
void				pars_dollar_2(t_command *com, size_t len_str, char **buf);
void				start_dollar(t_command *com, char **buf, char **buf_end);
void				pars_escaping(t_command *com, size_t len_str);
void				pars_redirect(char **line, t_command *com);
void				pars_reverse_redirect(char **line, t_command *com);
void				which_redirect(char **line, t_command *com);
void				start_redirect(t_command *com);
void				fill_redirect(t_command *com, size_t type_r);
void				fill_file_name(t_command *com, int i, t_arg *new);
void				file_open(t_command *com);
void				file_close(t_command *com);
void				error_redirect(t_command *com);
void				activate_pipe(char **line, t_command *com);
char				*ft_itoa(int n);
void				cmd_start(t_command *com);
int					cmd_echo(t_command *com);
int					cmd_cd(t_command *com);
int					cmd_pwd(t_command *com);
int					cmd_env(t_command *com);
int					error_message(char *message, int exit_code);
char				**error_message2(char *message);
int					cmd_export(t_command *com);
char				*detect_env_var(t_command *com, t_arg *arg);
t_env				*new_node(char *var, char *mean);
char				*find_meaning(t_command *com, t_arg *arg);
int					error_export(char *arg);
int					cmd_unset(t_command *com);
void				cmd_exit(t_command *com);
void				signal_handler(t_command *com);
void				*ctrl_d(t_command *com);
char				*find_bin(t_command *com);
int					free_mas(char **mass);
void				save_stdin_out(void);
int					redirect_input(t_command *com);
void				redirect_output(t_command *com);
void				return_stdin_out(void);
int					minishell_loop(t_command *com);
int					cmd_export_noargs(t_command *com);
void				function(int signal);
char				**envp_to_mass(t_command *com);
char				**transfer_to_mass(t_command *com);
void				check_if_my(char *cmd, t_command *com);
int					error_path(t_command *com);
int					prompt_message(void);

#endif
