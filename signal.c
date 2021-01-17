#include "minishell.h"

void	ctrl_c(int sig)
{
	sig = 0;
	write(1, "\n\r", 2);
	g_c_flag = 1;
	if (g_b_flag)
		exit(errno);
}

void	*ctrl_d(t_command *com)
{
	ft_putstr("exit\n");
	free_all(com, 0);
	exit(0);
}

void	ctrl_b(int sig)
{
	sig = 0;
	ft_putstr_fd("Quit: 3\n", 2);
}

void	signal_handler(t_command *com)
{
	signal(SIGINT, ctrl_c);
	if (g_c_flag)
		com->com_ret = 130;
	signal(SIGQUIT, ctrl_b);
	minishell_loop(com);
}
