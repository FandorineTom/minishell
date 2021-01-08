#include "minishell.h"

int		cmd_env(t_command *com)
{
	t_env *tmp;

	if (!com->env_def->env)
		tmp = com->env_def->next;
	else
		tmp = com->env_def;
	while (tmp)
	{
		ft_putstr_fd(tmp->env, com->comd->redir->fd2);
		ft_putchar_fd('=', com->comd->redir->fd2);
		ft_putstr_fd(tmp->meaning, com->comd->redir->fd2);
		ft_putchar_fd('\n', com->comd->redir->fd2);
		tmp = tmp->next;
	}
	return (0);
}