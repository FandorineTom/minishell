#include "minishell.h"

int	main()
{
	t_comd comd;
	t_flag flag;

	flag.flag = "n";
	flag.no_flag = 1;
	comd.cmnd = "echo";
	comd.env_var = NULL;
	comd.flag = &flag;
	cmd_start(&comd);
	return (0);
}