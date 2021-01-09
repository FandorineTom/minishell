#include "minishell.h"

void	 cmd_echo(t_command *com)
{
	int		flag;
	t_arg	*tmp;

	flag = 0;
	tmp = com->comd->arg;
	if (com->comd->flag->no_flag && !ft_strcmp(com->comd->flag->flag, "-n"))
		flag = 1;
	while (tmp && tmp->next)
	{
		ft_putstr_fd(tmp->arg, 1);
		ft_putchar_fd(' ', 1);
		tmp = tmp->next;
	}
	if (tmp && tmp->arg)
		ft_putstr_fd(tmp->arg, 1);
	if (!flag)
		ft_putchar_fd('\n', 1);
}