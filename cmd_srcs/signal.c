/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:10:45 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/20 17:32:01 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c(int sig)
{
	sig = 0;
	write(1, "\n\r", 2);
	if (g_b_flag)
		exit(errno);
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
	sig = 0;
	g_c_flag = 1;
	ft_putstr_fd("Quit: 3\n", 2);
	prompt_message();
}

void	signal_handler(t_command *com)
{
	signal(SIGINT, ctrl_c);
	if (g_c_flag)
		com->com_ret = 130;
	signal(SIGQUIT, ctrl_b);
}
