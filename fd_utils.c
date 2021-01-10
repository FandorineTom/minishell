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
		g_fdin = dup(com->comd->redir->fd2);
		close(com->comd->redir->fd2);
	}
	else
		g_fdin = dup(g_tmp_fd[0]);
}

void	redirect_output(t_command *com)
{
	if (com->comd->redir->type_red == 1 || com->comd->redir->type_red == 3)
	{
		g_fdout = dup(com->comd->redir->fd2);
		close(com->comd->redir->fd2);
	}
	else
		g_fdout = dup(g_tmp_fd[1]);
}