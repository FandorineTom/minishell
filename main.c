#include "minishell.h"

int	main()
{
	t_comd comd;
	t_flag flag;

	flag.flag = NULL;
	flag.no_flag = 0;
	comd.cmnd = "cd";
	comd.env_var = "test_dir";
	comd.flag = &flag;
	cmd_start(&comd);
	return (0);
}