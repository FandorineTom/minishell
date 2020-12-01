/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:40:09 by scopycat          #+#    #+#             */
/*   Updated: 2020/12/01 19:30:10 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_command *com, int i)
{
	(void)i;
	free_comd(com->comd);
	// free_arg(com->arg);
	// free_env(com->env_var);
	// if (!i)
	// 	free_env_def(com->env_def);
}

void	free_comd(t_comd *comd)
{
	t_comd	*buf;

	buf = comd;
	while (buf)
	{
		while(buf->next)
			buf = buf->next;
		free(buf->cmnd);
		free_flag(buf->flag);
		free(buf->env_var);
		free(buf);
		buf = comd;
		if (!buf->next)
			buf = NULL;
	}
	comd = NULL;
}

void	free_flag(t_flag *flag)
{
	t_flag	*buf;

	buf = flag;
	while (buf)
	{
		while(buf->next)
			buf = buf->next;
		free(buf->flag);
		free(buf);
		buf = flag;
		if (!buf->next)
			buf = NULL;
	}
	flag = NULL;
}