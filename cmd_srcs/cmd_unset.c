/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:10:26 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/18 14:10:27 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		cmd_unset(t_command *com)
{
	t_env	*tmp;
	t_env	*to_del;

	tmp = com->env_def;
	if (!com->comd->arg || !com->comd->arg->arg)
		return (0);
	while (com->env_def)
	{
		if (!(to_del = com->env_def->next))
			break ;
		if (!ft_strcmp(com->comd->arg->arg, to_del->env))
		{
			free(to_del->meaning);
			free(to_del->env);
			com->env_def->next = to_del->next;
			com->env_def = tmp;
			break ;
		}
		com->env_def = com->env_def->next;
	}
	com->env_def = tmp;
	return (0);
}