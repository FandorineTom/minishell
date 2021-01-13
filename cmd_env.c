#include "minishell.h"

int		cmd_env(t_command *com)
{
	t_env	*tmp;

	tmp = com->env_def;
	if (com->comd->arg && com->comd->arg->arg)
	{
		ft_putstr_fd("env: ", 2);
		ft_putstr_fd(com->comd->arg->arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
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