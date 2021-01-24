/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 15:28:20 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/24 15:30:42 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			copy_oldpwd(com);
			return (com->com_ret = check_pwd(com));
		}
		tmp = tmp->next;
	}
	return (1);
}
