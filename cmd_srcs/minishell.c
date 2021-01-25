/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:10:41 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/25 20:31:11 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			free_mas(char **mass)
{
	int		i;

	i = 0;
	if (!mass)
		return (0);
	while (mass && mass[i])
	{
		free(mass[i]);
		mass[i++] = NULL;
	}
	free(mass);
	mass = NULL;
	return (0);
}

int			free_str(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
	return (0);
}

static int	find_file(char *path, char *cmd)
{
	DIR				*dir;
	struct dirent	*dir_struct;

	if (!(dir = opendir(path)))
		return (0);
	while ((dir_struct = readdir(dir)))
	{
		if (!ft_strcmp(dir_struct->d_name, cmd))
		{
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

char		**find_path(t_command *com)
{
	t_env	*tmp;
	char	**path;

	tmp = com->env_def;
	path = NULL;
	while (tmp)
	{
		if (!ft_strcmp("PATH", tmp->env))
			path = ft_split(tmp->meaning, ':');
		tmp = tmp->next;
	}
	return (path);
}

char		*find_bin(t_command *com)
{
	char	**path;
	char	*to_ret;
	char	*tmp_line;
	int		i;

	if (com->comd->arg->arg[0] == '/' || com->comd->arg->arg[0] == '.')
		return (ft_strdup(com->comd->arg->arg));
	path = find_path(com);
	if (!path)
		com->com_ret = error_path(com, ": No such file or directory\n");
	i = -1;
	while (path && path[++i])
	{
		if (find_file(path[i], com->comd->arg->arg))
		{
			tmp_line = ft_strjoin("/", com->comd->arg->arg);
			to_ret = ft_strjoin(path[i], tmp_line);
			free(tmp_line);
			return (to_ret + free_mas(path));
		}
	}
	if (path)
		com->com_ret = error_path(com, ": command not found\n");
	free_mas(path);
	return (NULL);
}
