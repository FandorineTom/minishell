/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/13 13:04:29 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/18 13:16:20 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*detect_env_var(t_command *com, t_arg *arg)
{
	char	*var;
	int		i;

	i = 0;
	var = NULL;
	while(arg->arg[i] && arg->arg[i] != '=')
		i++;
	if (arg->arg[i] || (ft_isalpha(arg->arg[0]) && !arg->arg[i] \
	&& arg->arg[i - 1] == '='))
	{
		if (!(var = ft_substr(arg->arg, 0, i)))
		{
			com->com_ret = error_message(strerror(errno), 2);
			return (NULL);
		}
	}
	else
		com->com_ret = error_export(arg->arg);
	return (var == NULL ? NULL : var);
}

char	*find_meaning(t_command *com, t_arg *arg)
{
	char	*mean;
	int		i;
	int		len;

	i = 0;
	mean = NULL;
	while(arg->arg[i] && arg->arg[i] != '=')
		i++;
	if (arg->arg[i] == '=')
		i++;
	if (arg->arg[i])
	{
		len = ft_strlen(arg->arg);
		if (!(mean = ft_substr(arg->arg, i, len - i)))
		{
			com->com_ret = error_message(strerror(errno), 2);
			return (NULL);
		}
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
	t_arg	*tmp_a;

	tmp = com->env_def;
	tmp_a = com->comd->arg;
	if (!com->comd->arg || !com->comd->arg->arg)
		return (cmd_export_noargs(com));
	while (tmp_a)
	{
		flag = 0;
		if (!ft_isalpha(tmp_a->arg[0]))
			com->com_ret = error_export(tmp_a->arg);
		else if ((var_tochange = detect_env_var(com, tmp_a)))
		{
			mean = find_meaning(com, tmp_a);
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
			var_tochange = NULL;
			mean = NULL;
		}
		tmp_a = tmp_a->next;
	}
	return (0);
}