#include "minishell.h"

void	cmd_start(t_command *com)
{
	if (com->comd->no_command && !ft_strncmp(com->comd->cmnd, "echo", 4))
		cmd_echo(com);
	else if (com->comd->no_command && !ft_strncmp(com->comd->cmnd, "cd", 2))
		cmd_cd(com);
	else if (com->comd->no_command && !ft_strncmp(com->comd->cmnd, "pwd", 3))
		cmd_pwd();
	else if (com->comd->no_command && !ft_strncmp(com->comd->cmnd, "export", 6))
		cmd_export(com);
	else if (com->comd->no_command && !ft_strncmp(com->comd->cmnd, "unset", 5))
		cmd_unset(com);
	else if (com->comd->no_command && !ft_strncmp(com->comd->cmnd, "env", 3))
		cmd_env(com);
	if (com->comd->no_command && !ft_strncmp(com->comd->cmnd, "exit", 4))
		cmd_exit();
}