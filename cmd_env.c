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
		ft_putstr(tmp->env);
		ft_putchar('=');
		ft_putstr(tmp->meaning);
		ft_putchar('\n');
		tmp = tmp->next;
	}
	return (0);
}