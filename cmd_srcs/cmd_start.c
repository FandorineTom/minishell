/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 21:52:08 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/23 13:39:11 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	child_process(char *path, char **args, char **envp, t_command *com)
{
	if (execve(path, args, envp) == -1)
	{
		(void)(ft_putstr_fd(com->comd->arg->arg, 2) + ft_putstr_fd(": ", 2));
		free(path);
		free_mas(args);
		free_mas(envp);
		free_all(com, 1);
		exit(error_message("command not found", 127));
	}
}

int		parent_process(t_command *com)
{
	int		status;

	wait(&status);
	com->com_ret = WEXITSTATUS(status);
	if ((WIFSIGNALED(status)))
	{
		if (status == 131)
			ft_putstr_fd("Quit: 3\n", 2);
		return ((status != 131) ? 130 : status);
	}
	return (com->com_ret);
}

int		open_fork(t_command *com)
{
	pid_t		pid;
	char		*path;
	char		**args;
	char		**envp;

	if (!(path = find_bin(com)))
		return (com->com_ret);
	if (!(args = transfer_to_mass(com)))
		return (error_message("malloc error", 2));
	if (!(envp = envp_to_mass(com)))
		return (error_message("malloc error", 2));
	pid = fork();
	g_b_flag = 1;
	if (pid == 0)
		child_process(path, args, envp, com);
	else if (pid > 0)
		com->com_ret = parent_process(com);
	if (pid < 0)
		return (error_message(strerror(errno), 1));
	free(path);
	free_mas(args);
	free_mas(envp);
	g_b_flag = 0;
	return (com->com_ret);
}

void	start_pipe(t_command *com)
{
	int		fdpipe[2];

	while (com->comd)
	{
		dup2(g_fdin, 0);
		close(g_fdin);
		if (com->comd->redir->type_red == 1 || com->comd->redir->type_red == 3\
		|| !com->comd->next)
			redirect_output(com);
		else if (com->comd->next)
		{
			pipe(fdpipe);
			g_fdin = fdpipe[0];
			if (!g_fdout)
				g_fdout = fdpipe[1];
		}
		dup2(g_fdout, 1);
		close(g_fdout);
		g_fdout = 0;
		if (com->comd->no_command)
			check_if_my(com->comd->cmnd, com);
		else if (!com->comd->no_command && com->comd->arg)
			com->com_ret = open_fork(com);
		com->comd = com->comd->next;
	}
}

void	cmd_start(t_command *com)
{
	int		flag;
	t_comd	*tmp;
	t_redir	*tmp_r;

	if (com->comd->error_redir)
		return ;
	tmp_r = com->comd->redir;
	flag = 0;
	while (com->comd->redir)
	{
		if (com->comd->redir->type_red == 2)
		{
			redirect_input(com);
			flag = 1;
			break ;
		}
		com->comd->redir = com->comd->redir->previous;
	}
	com->comd->redir = tmp_r;
	if (!flag)
		redirect_input(com);
	tmp = com->comd;
	start_pipe(com);
	com->comd = tmp;
}
