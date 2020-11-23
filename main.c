#include "minishell.h"

int	main()
{
	t_comd comd;
	t_flag flag;

	flag.flag = NULL;
	flag.no_flag = 0;
	comd.cmnd = "pwd";
	comd.env_var = "test_dir";
	comd.flag = &flag;
	cmd_start(&comd);
	comd.cmnd = "cd";
	cmd_start(&comd);
	comd.cmnd = "pwd";
	cmd_start(&comd);
	// comd.env_var = "-";
	// cmd_start(&comd);
	// cmd_start(&comd);
	return (0);
}