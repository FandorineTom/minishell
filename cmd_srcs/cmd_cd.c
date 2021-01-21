/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:09:36 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/21 02:14:23 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

int		check_home(t_command *com)
{
	t_env	*tmp;
	int		flag;

	tmp = com->env_def;
	flag = 0;
	while (tmp)
	{
		if (!ft_strcmp("HOME", tmp->env))
			flag = 1;
		tmp = tmp->next;
	}
	if (!flag)
		return (0);
	return (1);
}

int		find_home(t_command *com)
{
	t_env	*tmp;

	tmp = com->env_def;
	while (tmp)
	{
		if (!ft_strcmp("HOME", tmp->env))
		{
			if (chdir(tmp->meaning) < 0)
				com->com_ret = error_message(strerror(errno), -1);
			return (com->com_ret);
		}
		tmp = tmp->next;
	}
	return (1);
}

int		change_tilda(t_command *com)
{
	t_env	*tmp;
	char	*path;

	tmp = com->env_def;
	while (tmp)
	{
		if (!ft_strcmp("HOME", tmp->env))
		{
			path = ft_substr(com->comd->arg->arg, 1, \
			ft_strlen(com->comd->arg->arg));
			path = ft_strjoin(tmp->meaning, path);
			if (chdir(path) < 0)
				com->com_ret = error_message(strerror(errno), -1);
			free(path);
			return (com->com_ret);
		}
		tmp = tmp->next;
	}
	return (1);
}

int		cmd_cd(t_command *com)
{
	char	pwd[1024];
	t_env	*tmp;

	getcwd(pwd, 1024);
	if (!check_home(com))
		return (error_message("minishell: cd: HOME not set", 1));
	tmp = com->env_def;
	while (tmp)
	{
		if (!ft_strcmp("OLDPWD", tmp->env))
		{
			free(tmp->meaning);
			tmp->meaning = ft_strdup(pwd);
		}
		tmp = tmp->next;
	}
	if (!com->comd->arg->arg)
		return (find_home(com));
	if (com->comd->arg->arg[0] == '~')
		return (change_tilda(com));
	if (chdir(com->comd->arg->arg) < 0)
		com->com_ret = error_message(strerror(errno), 1);
	return (com->com_ret);
}
