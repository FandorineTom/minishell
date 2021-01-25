/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:10:45 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/24 23:50:56 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c(int sig)
{
	(void)sig;
	write(1, "\n\r", 2);
	g_c_flag = 1;
	prompt_message();
}

void	*ctrl_d(t_command *com)
{
	ft_putstr("exit\n");
	free_all(com, 0);
	exit(0);
}

void	ctrl_b(int sig)
{
	char *code;
	
	code = ft_itoa(sig);
	g_c_flag = 1;
	if (g_b_flag)
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putendl_fd(code, 2);
		prompt_message();
	}
	else
	{
		g_c_flag = 2;
		ft_putstr_fd("\b\b  \b\b", 2);
	}
	free(code);
}

void	signal_handler(t_command *com)
{
	if (signal(SIGINT, ctrl_c) == SIG_ERR)
		com->com_ret = errno;
	if (g_c_flag == 1)
		com->com_ret = 130;
	signal(SIGQUIT, ctrl_b);
}
