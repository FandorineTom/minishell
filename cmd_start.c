#include "minishell.h"

void	cmd_start(t_command *com)
{
	if (!ft_strncmp(com->comd->cmnd, "echo", 4))
		cmd_echo(com);
	else if (!ft_strncmp(com->comd->cmnd, "cd", 2))
		cmd_cd(com);
	else if (!ft_strncmp(com->comd->cmnd, "pwd", 3))
		cmd_pwd();
	// else if (!ft_strncmp(comd->cmnd, "export", 6))
	// 	cmd_export(comd);
	// else if (!ft_strncmp(comd->cmnd, "unset", 5))
	// 	cmd_unset(comd);
	else if (!ft_strncmp(com->comd->cmnd, "env", 3))
		cmd_env(com);
	// else if (!ft_strncmp(comd->cmnd, "exit", 4))
	// 	cmd_exit(comd);
}