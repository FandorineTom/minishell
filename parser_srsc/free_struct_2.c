/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 10:58:54 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/21 14:23:32 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_arg(t_arg *arg)
{
	t_arg	*buf;

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
