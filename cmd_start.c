#include "minishell.h"

void	cmd_start(t_comd *comd)
{
	if (!ft_strncmp(comd->cmnd, "echo", 4))
		cmd_echo(comd);
	// if (!ft_strncmp(comd->cmnd, "cd", 2))
	// 	cmd_cd(comd);
	// if (!ft_strncmp(comd->cmnd, "pwd", 3))
	// 	cmd_pwd(comd);
	// if (!ft_strncmp(comd->cmnd, "export", 6))
	// 	cmd_export(comd);
	// if (!ft_strncmp(comd->cmnd, "unset", 5))
	// 	cmd_unset(comd);
	// if (!ft_strncmp(comd->cmnd, "env", 3))
	// 	cmd_env(comd);
	// if (!ft_strncmp(comd->cmnd, "exit", 4))
	// 	cmd_exit(comd);
}