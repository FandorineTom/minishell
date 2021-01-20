/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:10:20 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/20 17:23:07 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		cmd_pwd(t_command *com)
{
	char	*path;
	int		size;

	size = 1024;
	path = NULL;
	while (!(path = getcwd(NULL, size)))
	{
		size *= 2;
		if (size >= INT_MAX / 2)
			return (com->com_ret = error_message(strerror(errno), 2));
	}
	ft_putstr(path);
	ft_putchar('\n');
	return (0);
}
