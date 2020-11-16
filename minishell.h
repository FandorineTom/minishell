#ifndef MINISHELL_H
# define MINISHELL_H

#include "libft/libft.h"
#include "libft/get_next_line.h"

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

void				cmd_start(t_comd *comd);
void				cmd_echo(t_comd *comd);
int					cmd_cd(t_comd *comd);

#endif