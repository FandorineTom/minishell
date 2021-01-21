/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:10:00 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/21 17:42:43 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_isnumber(char *s)
{
	int	i;
	int	res;

	if (!s || !s[0])
		return (0);
	i = -1;
	res = 1;
	if (*s == '-')
		s++;
	while (s[++i] && res)
	{
		if (!ft_isdigit(s[i]))
			res = 0;
	}
	return (res);
}

void	cmd_exit(t_command *com)
{
	ft_putstr("exit\n");
	if (com->comd->arg && !com->comd->arg->next)
	{
		if(com->comd->arg->arg)
		{
			if (ft_isnumber(com->comd->arg->arg))
				com->com_ret = ft_atoi(com->comd->arg->arg);
			else
			{
				ft_putstr_fd("minishell: exit: ", 2);
				ft_putstr_fd(com->comd->arg->arg, 2);
				ft_putstr_fd(": numeric argument required\n", 2);
			}
		}
	}
	else
	{
		com->com_ret = error_message("bash: exit: too many arguments", 1);
		return ;
	}
	free_all(com, 0);
	exit(com->com_ret);
}
