/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:45:37 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/21 14:23:25 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_com(t_command *com)
{
	int i;

	i = 0;
	init_comd(com);
	com->quotes_op = 0;
	com->env_var = NULL;
	com->error = 0;
	com->no_var = 1;
	com->pipe_count = 0;
	while (i < 100)
		com->process[i++] = 0;
}

void	init_comd(t_command *com)
{
	com->comd = (t_comd*)malloc(sizeof(t_comd));
	com->comd->cmnd = NULL;
	init_flag(com);
	init_redirect(com);
	init_arg(com);
	com->comd->no_command = 1;
	com->comd->env_var = NULL;
	com->comd->pipe_l = 0;
	com->comd->pipe_r = 0;
	com->comd->error_redir = 0;
	com->comd->next = NULL;
	com->comd->previous = NULL;
}

void	init_redirect(t_command *com)
{
	com->comd->redir = (t_redir*)malloc(sizeof(t_redir));
	com->comd->redir->fd1 = 0;
	com->comd->redir->fd2 = 1;
	com->comd->redir->file_name = NULL;
	com->comd->redir->l_redir = 0;
	com->comd->redir->r_redir = 0;
	com->comd->redir->type_red = 0;
	com->comd->redir->next = NULL;
	com->comd->redir->previous = NULL;
}

void	init_flag(t_command *com)
{
	com->comd->flag = (t_flag*)malloc(sizeof(t_flag));
	com->comd->flag->flag = NULL;
	com->comd->flag->no_flag = 1;
	com->comd->flag->next = NULL;
}

void	init_arg(t_command *com)
{
	com->comd->arg = (t_arg*)malloc(sizeof(t_arg));
	com->comd->arg->arg = NULL;
	com->comd->arg->path = NULL;
	com->comd->arg->no_arg = 1;
	com->comd->arg->next = NULL;
	com->comd->arg->previous = NULL;
}
