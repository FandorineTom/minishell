/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_start.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 21:52:08 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/12 13:03:51 by snorthmo         ###   ########.fr       */
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
		cmd_echo(com);
	else if (cmd_num == 1)
		cmd_cd(com);
	else if (cmd_num == 2)
		cmd_pwd();
	else if (cmd_num == 3)
		cmd_export(com);
	else if (cmd_num == 4)
		cmd_unset(com);
	else if (cmd_num == 5)
		cmd_env(com);
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

	pid = fork();
	if (pid == 0)
	{
		path = find_bin(com);
		args = transfer_to_mass(com);
		envp = envp_to_mass(com);
		execve(path, args, envp); // надо тут освободить все, если результат этой функции = -1
	}
	else if (pid > 0)
		wait(&status); // а тут надо посмотреть через WEXITSTATUS и прочие что возвращается и выходить соответсвенно
	if (pid < 0)
		g_for_exit = error_message(strerror(errno), 1); // а отсюда по идее надо выходить совсем и завершать программу? 
}

void	cmd_start(t_command *com)
{
	int		fdpipe[2];
	t_comd	*tmp;

	if (com->comd->error_redir)
		return ; // это если нет такого файла или еще какая-то ошибка с файлом
	tmp = com->comd;
	redirect_input(com);
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
		else
			return ;// здесь выходит если нет команды и нет вообще ничего, что мы делаем в этом случае и может ли такое быть
		com->comd = com->comd->next;
	}
	com->comd = tmp;
}
	

 