#include "minishell.h"

void	save_stdin_out(void)
{
	g_tmp_fd[0] = dup(0);
	g_tmp_fd[1] = dup(1);
}

void	return_stdin_out(void)
{
	dup2(g_tmp_fd[0], 0);
	dup2(g_tmp_fd[1], 1);
	close(g_tmp_fd[0]);
	close(g_tmp_fd[1]);
}

void	redirect_input(t_command *com)
{
	if (com->comd->redir->type_red == 2)
	{
		dup2(com->comd->redir->fd2, g_fdin);
		close(com->comd->redir->fd2);
	}
	else
		g_fdin = dup(g_tmp_fd[0]);
}

void	redirect_output(t_command *com)
{
	if (com->comd->redir->type_red == 1 || com->comd->redir->type_red == 3)
	{
		dup2(com->comd->redir->fd2, g_fdout);
		close(com->comd->redir->fd2);
	}
	else
		g_fdout = dup(g_tmp_fd[1]);
}