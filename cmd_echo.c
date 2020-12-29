#include "minishell.h"

void	 cmd_echo(t_command *com)
{
	int		flag;
	t_arg	*tmp;

	flag = 0;
	tmp = com->comd->arg;
	if (com->comd->flag->no_flag && !ft_strcmp(com->comd->flag->flag, "-n"))
		flag = 1;
	while (tmp->next)
	{
		ft_putstr(tmp->arg);
		ft_putchar(' ');
		tmp = tmp->next;
	}
	ft_putstr(tmp->arg);
	if (!flag)
		ft_putchar('\n');
}