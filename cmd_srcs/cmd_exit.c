/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:10:00 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/24 15:24:41 by snorthmo         ###   ########.fr       */
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

void	print_error_exit(char *line)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

int		cmd_exit(t_command *com)
{
	int		i;
	int		res;

	ft_putstr("exit\n");
	if (com->comd->arg && (i = ft_isnumber(com->comd->arg->arg)) \
	&& com->comd->arg->next)
		return (error_message("bash: exit: too many arguments", 1));
	else if (com->comd->arg && com->comd->arg->arg)
	{
		res = ft_atoi(com->comd->arg->arg);
		if (!i || (res == 0 && com->comd->arg->arg[0] != '0' \
		&& ft_strcmp("-9223372036854775808", com->comd->arg->arg)))
			print_error_exit(com->comd->arg->arg);
		if (i && (res != 0 || (res == 0 && com->comd->arg->arg[0] == '0')))
			com->com_ret = res;
		else
			com->com_ret = 255;
	}
	free_all(com, 0);
	exit(com->com_ret);
}
