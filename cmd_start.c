/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 21:52:08 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/13 16:43:38 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_if_my(char *cmd, t_command *com)
{
	const char	*my_str[7] = {"echo", "cd", "pwd", "export", "unset", "env",
							"exit"};
	int			i;
	int			cmd_num;

	i = -1;
	while(++i < 7)
		if (!ft_strcmp(cmd, my_str[i]))
			cmd_num = i;
	if (cmd_num == 0)
		com->com_ret = cmd_echo(com);
	else if (cmd_num == 1)
		cmd_cd(com);
	else if (cmd_num == 2)
		com->com_ret = cmd_pwd(com);
	else if (cmd_num == 3)
		com->com_ret = cmd_export(com);
	else if (cmd_num == 4)
		com->com_ret = cmd_unset(com);
	else if (cmd_num == 5)
		com->com_ret = cmd_env(com);
	else if (cmd_num == 6)
		cmd_exit();
}

char	**envp_to_mass(t_command *com)
{
	char	**envp;
	t_env	*tmp;
	int		len;

	tmp = com->env_def;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	if (!(envp = (char **)ft_calloc(sizeof(char *), len + 1)))
		return ((error_message2(strerror(errno))));
	tmp = com->env_def;
	len = 0;
	while (tmp)
	{
		if (!(envp[len] = ft_strjoin(tmp->env, "=")))
			return(error_message2(strerror(errno)));
		if (!(envp[len] = ft_strjoin(envp[len], tmp->meaning)))
			return(error_message2(strerror(errno)));
		len++;
		tmp = tmp->next;
	}
	envp[len] = NULL;
	return (envp);
}

char	**transfer_to_mass(t_command *com)
{
	char	**args;
	t_arg	*tmp_a;
	int		len;
	int		i;

	len = 0;
	i = 0;
	tmp_a = com->comd->arg;
	while (tmp_a)
	{
		len++;
		tmp_a = tmp_a->next;
	}
	if (!(args = (char **)ft_calloc(sizeof(char *), len + 1)))
		return (error_message2(strerror(errno)));
	tmp_a = com->comd->arg;
	while (tmp_a)
	{
		if (!(args[i++] = ft_strdup(tmp_a->arg)))
			return(error_message2(strerror(errno)));
		tmp_a = tmp_a->next;
	}
	args[i] = NULL;
	return (args);
}

void	open_fork(t_command *com)
{
	int			status;
	pid_t		pid;
	char		*path;
	char		**args;
	char		**envp;

	path = find_bin(com);
	args = transfer_to_mass(com);
	envp = envp_to_mass(com);
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, args, envp) == -1)
		{
			(void)(ft_putstr_fd(com->comd->arg->arg, 2) + ft_putstr_fd(": ", 2));
			free(path);
			free_mas(args);
			free_mas(envp);
			free_all(com, 1);
			exit(error_message("command not found\n", 127));
		}
	}
	else if (pid > 0)
	{
		wait(&status);
		com->com_ret = WEXITSTATUS(status);
		if ((WIFSIGNALED(status)))
		{
			if (status == 131)
				ft_putstr_fd("^\\Quit: 3\n", 2);
			com->com_ret = (status != 131) ? 130 : status;
		}
	}
	if (pid < 0)
		com->com_ret = error_message(strerror(errno), 1);
	free(path);
	free_mas(args);
	free_mas(envp);
}

void	cmd_start(t_command *com)
{
	int		fdpipe[2];
	int		flag;
	t_comd	*tmp;
	t_redir	*tmp_r;

	if (com->comd->error_redir)
		return ; // это если нет такого файла или еще какая-то ошибка с файлом
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
	while (com->comd)
	{
		dup2(g_fdin, 0);
		close(g_fdin);
		if (!com->comd->next)
			redirect_output(com);
		else
		{
			pipe(fdpipe);
			g_fdin = fdpipe[0];
			g_fdout = fdpipe[1];
		}
		dup2(g_fdout, 1);
		close(g_fdout);
		if (com->comd->no_command)
			check_if_my(com->comd->cmnd, com);
		else if (!com->comd->no_command && com->comd->arg)
			open_fork(com);
		com->comd = com->comd->next;
	}
	com->comd = tmp;
}
	

 