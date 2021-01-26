/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:58:54 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/26 15:48:00 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arg(t_arg *arg)
{
	t_arg	*buf;

	while (arg && arg->previous)
		arg = arg->previous;
	while (arg)
	{
		buf = arg;
		arg = arg->next;
		if (buf->arg)
			free(buf->arg);
		buf->arg = NULL;
		if (buf->path)
			free(buf->path);
		buf->path = NULL;
		free(buf);
		buf = NULL;
	}
}

void	skip_spaces(char **line)
{
	while (**line == ' ')
		(*line)++;
}
