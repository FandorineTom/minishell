/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:10:20 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/18 14:10:22 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		cmd_pwd(t_command *com)
{
	char	path[1024];

	if (!(getcwd(path, 1024)))
		return (com->com_ret = error_message(strerror(errno), 2));
	ft_putstr(path);
	ft_putchar('\n');
	return (0);
}