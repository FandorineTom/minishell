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
		ft_putstr_fd(tmp->env, 1);
		ft_putchar_fd('=', 1);
		ft_putstr_fd(tmp->meaning, 1);
		ft_putchar_fd('\n', 1);
		tmp = tmp->next;
	}
	return (0);
}