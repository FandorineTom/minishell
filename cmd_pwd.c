#include "minishell.h"

int		cmd_pwd(void)
{
	char	path[1024];

	getcwd(path, 1024);
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
	return (0);
}