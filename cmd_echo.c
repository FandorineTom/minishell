#include "minishell.h"

void	 cmd_echo(t_comd *comd)
{
	int		flag;

	flag = 0;
	if (comd->flag->no_flag && !ft_strcmp(comd->flag->flag, "n"))
		flag = 1;
	if (comd->env_var)
		ft_putstr(comd->env_var);
	if (!flag)
		ft_putstr("\n");
}