#include "minishell.h"

int		free_mas(char **mass)
{
	int		i;

	i = 0;
	while (mass && mass[i])
		free(mass[i++]);
	free(mass);
	mass = NULL;
	return (0);
}

int		free_str(char **str)
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

char	*find_bin(t_command *com)
{
	char	**path;
	char	*to_ret;
	char	*help;
	int		i;
	t_env	*tmp;

	tmp = com->env_def;
	while (tmp)
	{
		if (!ft_strcmp("PATH", tmp->env))
			path = ft_split(tmp->meaning, ':');
		tmp = tmp->next;
	}
	i = -1;
	while(path && path[++i])
	{
		if (find_file(path[i], com->comd->arg->arg))
		{
			help = ft_strjoin("/", com->comd->arg->arg);
			to_ret = ft_strjoin(path[i], help);
			return(to_ret + free_mas(path) + free_str(&help));
		}
	}
	free_mas(path);
	return (NULL); //надо подумать, что возвращать, если ничего не нашел
}