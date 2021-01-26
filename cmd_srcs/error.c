/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:10:30 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/26 18:46:02 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		error_message(char *message, int exit_code)
{
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	errno = 0;
	return (exit_code);
}

char	**error_message2(char *message)
{
	ft_putstr(message);
	ft_putchar_fd('\n', 2);
	errno = 0;
	return (NULL);
}

int		error_path(t_command *com, char *message)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(com->comd->arg->arg, 2);
	ft_putstr_fd(message, 2);
	return (127);
}

int		error_export(char *arg)
{
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	return (1);
}

int		free_str(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
	return (0);
}
