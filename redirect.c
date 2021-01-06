/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:35:45 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/06 19:19:20 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_open(t_command *com)
{
	t_redir	*tmp;

	tmp = com->comd->redir;
	while (com->comd->redir)
	{
		if (com->comd->redir->type_red == 1)
			com->comd->redir->fd2 = open(com->comd->redir->file_name, \
				O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (com->comd->redir->type_red == 3)
			com->comd->redir->fd2 = open(com->comd->redir->file_name, \
				O_RDWR | O_CREAT | O_APPEND, 0666);
		if (com->comd->redir->type_red == 2)
			com->comd->redir->fd2 = 0;
		com->comd->redir = com->comd->redir->next;
	}
	com->comd->redir = tmp;
	while(com->comd->redir->next)
		com->comd->redir = com->comd->redir->next;
}

void	file_close(t_command *com)
{
	t_redir	*tmp;

	while (com->comd->redir->previous)
		com->comd->redir = com->comd->redir->previous;
	tmp = com->comd->redir;
	while (com->comd->redir)
	{
		if (com->comd->redir->type_red == 1 || com->comd->redir->type_red == 3)
		close(com->comd->redir->fd2);
		com->comd->redir->fd2 = 1;
		com->comd->redir = com->comd->redir->next;
	}
	com->comd->redir = tmp;
}