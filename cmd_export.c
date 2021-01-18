#include "minishell.h"

char	*detect_env_var(t_command *com)
{
	char	*var;
	int		i;

	i = 0;
	while(com->comd->arg->arg[i] && com->comd->arg->arg[i] != '=')
		i++;
	if (com->comd->arg->arg[i])
	{
		if (!(var = ft_substr(com->comd->arg->arg, 0, i)))
		{
			error_message(strerror(errno), -1);
			return (NULL);
		}
	}
	else
	{
		error_export(com);
		return (NULL);
	}
	return (var);
}

char	*find_meaning(t_command *com)
{
	char	*mean;
	int		i;
	int		len;

	i = 0;
	while(com->comd->arg->arg[i] != '=')
		i++;
	len = ft_strlen(com->comd->arg->arg);
	if (!(mean = ft_substr(com->comd->arg->arg, i + 1, len - i + 1)))
	{
		error_message(strerror(errno), -1);
		return (NULL);
	}
	return (mean);
}

t_env	*new_node(char *var, char *mean)
{
	t_env *elem;

	if (!(elem = (t_env *)malloc(sizeof(t_env))))
	{
		error_message(strerror(errno), -1);
		return (NULL);
	}
	elem->env = ft_strdup(var);
	elem->meaning = ft_strdup(mean);
	elem->next = NULL;
	return (elem);
}

int		cmd_export(t_command *com)
{
	t_env	*tmp;
	char	*var_tochange;
	char	*mean;
	int		flag;

	tmp = com->env_def;
	flag = 0;
	if (!com->comd->arg || !com->comd->arg->arg)
		return (cmd_export_noargs(com));
	if (!(var_tochange = detect_env_var(com)))
		return (0);								// обработать эту ошибку тут!! Это если в аргументах нет =
	mean = find_meaning(com);
	while (com->env_def && !flag)
	{
		if (!ft_strcmp(var_tochange, com->env_def->env))
		{
			free(com->env_def->meaning);
			com->env_def->meaning = ft_strdup(mean);
			flag = 1;
		}
		com->env_def = com->env_def->next;
	}
	com->env_def = tmp;
	if (!flag)
		ft_envadd_back(&com->env_def, new_node(var_tochange, mean)); 
	free(var_tochange);
	free(mean);
	return (0);
}