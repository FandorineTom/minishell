#include "minishell.h"

// void	*ctrl_c(t_command *com)
// {
	
// }

void	*ctrl_d(t_command *com)
{
	ft_putstr("exit\n");
	free_all(com, 0);
	exit(0);
}

void	signal_handler(t_command *com)
{
	signal(SIGINT, ctrl_d(com));
}
