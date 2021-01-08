#include "minishell.h"

int		cmd_pwd(t_command *com)
{
	char	path[1024];

	getcwd(path, 1024);
	ft_putstr_fd(path, com->comd->redir->fd2);
	ft_putchar_fd('\n', com->comd->redir->fd2);
	return (0);
}