/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:45:37 by scopycat          #+#    #+#             */
/*   Updated: 2020/12/19 17:14:07 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_com(t_command *com)
{
	int i;
	
	i = 0;
	init_comd(com);
	// init_arg(com);
	// init_env_d(com);
	com->quotes_op = 0;
	com->env_var = NULL;
	com->error = 0;
	// com->no_arg = 1; // в целом тут можно не инициализировать, потому что дальше инициализируетя (эти три счетчика)
	com->no_command = 1;
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
	com->comd->no_command = 1;
	com->comd->env_var = NULL;
	com->comd->pipe_l = 0;
	com->comd->pipe_r = 0;
	com->comd->next = NULL;
}

void	init_redirect(t_command *com)
{
	com->comd->redir.fd1 = 0; // проверить, чтобы именно эти были значения по умолчанию
	com->comd->redir.fd2 = 1;
	com->comd->redir.l_redir = 0;
	com->comd->redir.r_redir = 0;
	com->comd->redir.type_red = 0; // если > - 1, если < - 2, если >> - 3, если <> - 4
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
	com->comd->arg->wildcard = 0;
	com->comd->arg->no_arg = 1;
	com->comd->arg->next = NULL;
}

void	init_env_d(t_command *com)
{
	com->env_def = (t_env*)malloc(sizeof(t_env));
	com->env_def->env = NULL;
	com->env_def->meaning = NULL;
	com->env_def->next = NULL;
}