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
		ft_putstr_fd(tmp->arg, com->comd->redir->fd2);
		ft_putchar_fd(' ', com->comd->redir->fd2);
		tmp = tmp->next;
	}
	if (tmp && tmp->arg)
		ft_putstr_fd(tmp->arg, com->comd->redir->fd2);
	if (!flag)
		ft_putchar_fd('\n', com->comd->redir->fd2);
}