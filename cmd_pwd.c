#include "minishell.h"

int		cmd_pwd(void)
{
	char	path[1024];

	getcwd(path, 1024);
	ft_putstr(path);
	return (0);
}