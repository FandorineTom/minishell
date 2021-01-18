/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:09:47 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/18 15:38:58 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		cmd_echo(t_command *com)
{
	int		flag;
	t_arg	*tmp;

	flag = 0;
	tmp = com->comd->arg;
	if (com->comd->flag->no_flag && !ft_strcmp(com->comd->flag->flag, "-n"))
		flag = 1;
	while (tmp && tmp->next)
	{
		ft_putstr(tmp->arg);
		ft_putchar(' ');
		tmp = tmp->next;
	}
	if (tmp && tmp->arg)
		ft_putstr(tmp->arg);
	if (!flag)
		ft_putchar('\n');
	return (0);
}
