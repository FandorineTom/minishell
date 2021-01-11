/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 17:35:45 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/11 21:56:51 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_open(t_command *com)
{
	t_redir	*tmp;

	tmp = com->comd->redir;
	while (com->comd->redir && !com->comd->error_redir)
	{
		if (com->comd->redir->type_red == 1)
			com->comd->redir->fd2 = open(com->comd->redir->file_name, \
				O_RDWR | O_CREAT | O_TRUNC, 0666);
		if (com->comd->redir->type_red == 3)
			com->comd->redir->fd2 = open(com->comd->redir->file_name, \
				O_RDWR | O_CREAT | O_APPEND, 0666);
		if (com->comd->redir->type_red == 2)
			com->comd->redir->fd2 = open(com->comd->redir->file_name, \
				O_RDONLY);
		if (com->comd->redir->fd2 == -1)
			error_redirect(com);
		com->comd->redir = com->comd->redir->next;
	}
	com->comd->redir = tmp;
	while(com->comd->redir->next)
		com->comd->redir = com->comd->redir->next;
}

void	error_redirect(t_command *com)
{
	com->comd->redir->fd2 = 1;
	ft_putstr(com->comd->redir->file_name);
	write(2, ": No such file or directory\n", 28);
	com->comd->error_redir = 1;
	com->comd->redir->type_red = 0;
	// com->comd->redir->r_redir = 0;
}

void	file_close(t_command *com)
{
	t_redir	*tmp;

	while (com->comd->redir->previous)
		com->comd->redir = com->comd->redir->previous;
	tmp = com->comd->redir;
	while (com->comd->redir)
	{
		if (com->comd->redir->type_red) // == 1 || com->comd->redir->type_red == 3)
			close(com->comd->redir->fd2);
		com->comd->redir->fd2 = 1;
		com->comd->redir = com->comd->redir->next;
	}
	com->comd->redir = tmp;
}

void	start_redirect(t_command *com)
{
	while (com->comd && com->comd->next)
	{
		if (com->comd->redir && com->comd->redir->r_redir)
			file_open(com);
		com->comd = com->comd->next;	
	}
	if (com->comd->redir && com->comd->redir->r_redir)
		file_open(com);
	while (com->comd->previous)
		com->comd = com->comd->previous;
}