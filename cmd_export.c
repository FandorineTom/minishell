/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:04:29 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/13 17:41:50 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*detect_env_var(t_command *com)
{
	char	*var;
	t_arg	*tmp;
	int		i;
	int		flag;

	i = 0;
	var = NULL;
	tmp = com->comd->arg;
	flag = 0;
	while (tmp)
	{
		i = 0;
		while(tmp->arg[i] && tmp->arg[i] != '=')
			i++;
		if (tmp->arg[i])
		{
			if (!(var = ft_substr(tmp->arg, 0, i)))
			{
				com->com_ret = error_message(strerror(errno), 2);
				return (NULL);
			}
		}
		else if (!flag)
		{
			com->com_ret = error_export(com);
			flag = 1;
		}
		tmp = tmp->next;
	}
	return (var == NULL ? NULL : var);
}

char	*find_meaning(t_command *com)
{
	char	*mean;
	int		i;
	int		len;
	t_arg	*tmp;

	i = 0;
	tmp = com->comd->arg;
	mean = NULL;
	while (tmp)
	{
		i = 0;
		while(tmp->arg[i] != '=')
			i++;
		if (tmp->arg[i])
		{
			len = ft_strlen(tmp->arg);
			if (!(mean = ft_substr(tmp->arg, i + 1, len - i + 1)))
			{
				com->com_ret = error_message(strerror(errno), 2);
				return (NULL);
			}
		}
		tmp = tmp->next;
	}
	return (mean == NULL ? NULL : mean);
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
	if (!(var_tochange = detect_env_var(com)) || !(mean = find_meaning(com)))
		return (com->com_ret);
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