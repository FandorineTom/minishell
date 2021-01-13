#include "minishell.h"

int		cmd_pwd(t_command *com)
{
	char	path[1024];

	if (!(getcwd(path, 1024)))
		return (com->com_ret = error_message(strerror(errno), 2));
	ft_putstr(path);
	ft_putchar('\n');
	return (0);
}