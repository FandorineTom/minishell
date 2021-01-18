#include "minishell.h"

int		cmd_export_noargs(t_command *com)
{
	t_env *tmp;

	tmp = com->env_def;
	while (tmp)
	{
		ft_putstr("declare -x ");
		ft_putstr(tmp->env);
		ft_putstr("=\"");
		ft_putstr(tmp->meaning);
		ft_putchar('"');
		ft_putchar('\n');
		tmp = tmp->next;
	}
	return (0);
}