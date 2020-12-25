#include "minishell.h"

void	 cmd_echo(t_command *com)
{
	int		flag;

	flag = 0;
	if (com->comd->flag->no_flag && !ft_strcmp(com->comd->flag->flag, "-n"))
		flag = 1;
	if (com->comd->arg && com->comd->arg->arg)
		ft_putstr(com->comd->arg->arg);
	if (!flag)
		ft_putstr("\n");
}