#include "minishell.h"

int		cmd_cd(t_comd *comd)
{
	char	path[1024];

	getcwd(path, 1024);
	ft_printf("%s\n", path);
	chdir(comd->env_var);
	getcwd(path, 1024);
	ft_printf("%s\n", path);
	return (0);
}