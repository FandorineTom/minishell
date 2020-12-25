#include "minishell.h"

int		cmd_env(t_command *com)
{
	t_env *tmp;

	tmp = com->env_def;
	while (tmp->next)
	{
		ft_putstr(tmp->env);
		ft_putchar('=');
		ft_putstr(tmp->meaning);
		ft_putchar('\n');
		tmp = tmp->next;
	}
	return (0);
}