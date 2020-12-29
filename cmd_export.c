#include "minishell.h"

char	*detect_env_var(t_command *com)
{
	char	*var;
	int		i;

	i = 0;
	while(com->comd->arg->arg[i] != '=')
		i++;
	if (!(var = (char *)ft_calloc(sizeof(char), i)))
	{
		error_message(strerror(errno), -1);
		return (NULL);
	}
	i = 0;
	while (*(com->comd->arg->arg) != '=')
	{
		var[i++] = *(com->comd->arg->arg);
		com->comd->arg->arg++;
	}
	com->comd->arg->arg++;
	return (var);
}

char	*find_meaning(t_command *com)
{
	char	*mean;
	int		i;

	i = 0;
	while(com->comd->arg->arg[i])
		i++;
	if (!(mean = (char *)ft_calloc(sizeof(char), i)))
	{
		error_message(strerror(errno), -1);
		return (NULL);
	}
	i = 0;
	while (*(com->comd->arg->arg))
	{
		mean[i++] = *(com->comd->arg->arg);
		com->comd->arg->arg++;
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
	elem->env = var;
	elem->meaning = mean;
	elem->next = NULL;
	return (elem);
}

int		cmd_export(t_command *com)
{
	t_env	*tmp;
	char	*var_tochange;
	int		flag;

	tmp = com->env_def;
	flag = 0;
	var_tochange = detect_env_var(com);
	while (com->env_def->next)
	{
		if (!ft_strcmp(var_tochange, com->env_def->env)) // что-то здесь не так, надо выяснить, что!!!
		{
			com->env_def->meaning = var_tochange; // надо уточнить можно ли так вообще...
			flag = 1;
		}
		com->env_def = com->env_def->next;
	}
	if (!flag)
	{
		com->env_def->next = new_node(var_tochange, find_meaning(com));
	}
	com->env_def = tmp;
	return (0);
}