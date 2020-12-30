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
	// free(com->comd->arg->arg); // по хорошему тут указатель надо вернуть на начало строки и только потом освобождать
	com->comd->arg->arg = NULL;
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
	int		flag;

	tmp = com->env_def;
	flag = 0;
	var_tochange = detect_env_var(com);
	if (!com->env_def->env && com->env_def->next)
		com->env_def = com->env_def->next;
	while (com->env_def && !flag)
	{
		if (!ft_strcmp(var_tochange, com->env_def->env))
		{
			free(com->env_def->meaning);
			com->env_def->meaning = ft_strdup(find_meaning(com));
			flag = 1;
		}
		com->env_def = com->env_def->next;
	}
	com->env_def = tmp;
	if (!flag)
		ft_envadd_back(&com->env_def, new_node(var_tochange, find_meaning(com))); 
	free(var_tochange);
	return (0);
}