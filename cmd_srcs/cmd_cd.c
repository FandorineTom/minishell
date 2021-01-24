/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:09:36 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/24 15:28:40 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			copy_oldpwd(com);
			return (com->com_ret = check_pwd(com));
		}
		tmp = tmp->next;
	}
	return (1);
}

int		change_back(t_command *com)
{
	t_env	*tmp;
	char	*path;

	tmp = com->env_def;
	while (tmp)
	{
		if (!ft_strcmp("OLDPWD", tmp->env))
		{
			path = ft_strdup(tmp->meaning);
			if (chdir(path) < 0)
				com->com_ret = error_message(strerror(errno), -1);
			ft_putendl_fd(path, 1);
			free(path);
			copy_oldpwd(com);
			return (com->com_ret = check_pwd(com));
		}
		tmp = tmp->next;
	}
	return (com->com_ret = error_message("minishell: cd: OLDPWD not set", 127));
}

int		check_pwd(t_command *com)
{
	t_env	*tmp;
	char	*pwd;
	int		size;

	size = 1024;
	pwd = NULL;
	tmp = com->env_def;
	while (!(pwd = getcwd(NULL, size)))
	{
		size *= 2;
		if (size >= INT_MAX / 2)
			return (com->com_ret = error_message(strerror(errno), 2));
	}
	while (tmp)
	{
		if (!ft_strcmp("PWD", tmp->env) && ft_strcmp(pwd, tmp->meaning))
		{
			free(tmp->meaning);
			tmp->meaning = ft_strdup(pwd);
		}
		tmp = tmp->next;
	}
	free(pwd);
	return (com->com_ret);
}

void	copy_oldpwd(t_command *com)
{
	t_env	*tmp;
	t_env	*pwd;
	t_env	*oldpwd;

	tmp = com->env_def;
	pwd = NULL;
	oldpwd = NULL;
	while (tmp)
	{
		if (!ft_strcmp("PWD", tmp->env))
			pwd = tmp;
		if (!ft_strcmp("OLDPWD", tmp->env))
			oldpwd = tmp;
		if (!tmp->next && !oldpwd && pwd)
		{
			ft_envadd_back(&com->env_def, new_node("OLDPWD", pwd->meaning));
			return ;
		}
		tmp = tmp->next;
	}
	if (pwd && oldpwd)
	{
		free(oldpwd->meaning);
		oldpwd->meaning = ft_strdup(pwd->meaning);
	}
}

int		cmd_cd(t_command *com)
{
	if (!check_home(com))
		return (error_message("minishell: cd: HOME not set", 1));
	if (!com->comd->arg->arg)
		return (find_home(com));
	if (com->comd->arg->arg[0] == '~')
		return (change_tilda(com));
	if (com->comd->arg->arg[0] == '-')
		return (change_back(com));
	if (chdir(com->comd->arg->arg) < 0)
		com->com_ret = error_message(strerror(errno), 1);
	copy_oldpwd(com);
	return (com->com_ret = check_pwd(com));
}
