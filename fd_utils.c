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
	if (com->comd->pipe_l)
	{
		dup2(com->comd->redir->fd1, 0);
		close(com->comd->redir->fd1);
	}
}

void	redirect_output(t_command *com)
{
	if (com->comd->pipe_r)
	{
		dup2(com->comd->redir->fd2, 1);
		close(com->comd->redir->fd2);
	}
}