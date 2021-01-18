/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:10:36 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/18 14:10:37 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int		redirect_input(t_command *com)
{
	if (com->comd->redir->type_red == 2)
	{
		g_fdin = dup(com->comd->redir->fd2);
		close(com->comd->redir->fd2);
		return (1);
	}
	else
		g_fdin = dup(g_tmp_fd[0]);
	return (0);
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