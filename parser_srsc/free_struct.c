/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:40:09 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/21 14:23:31 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(t_command *com, int i)
{
	(void)i;
	free_comd(com->comd);
	if (com->env_var)
		free(com->env_var);
	com->env_var = NULL;
	if (!i)
		free_env(com->env_def);
}

void	free_comd(t_comd *comd)
{
	t_comd	*buf;

	while (comd)
	{
		buf = comd;
		comd = comd->next;
		if (buf->cmnd)
			free(buf->cmnd);
		buf->cmnd = NULL;
		free_flag(buf->flag);
		free_redirect(buf->redir);
		free_arg(buf->arg);
		if (buf->env_var)
			free(buf->env_var);
		buf->env_var = NULL;
		free(buf);
		buf = NULL;
	}
}

void	free_redirect(t_redir *red)
{
	t_redir	*buf;

	while (red)
	{
		buf = red;
		red = red->next;
		if (buf->file_name)
			free(buf->file_name);
		buf->file_name = NULL;
		free(buf);
		buf = NULL;
	}
}

void	free_flag(t_flag *flag)
{
	t_flag	*buf;

	while (flag)
	{
		buf = flag;
		flag = flag->next;
		if (buf->flag)
			free(buf->flag);
		buf->flag = NULL;
		if (buf)
			free(buf);
		buf = NULL;
	}
}

void	free_env(t_env *env_def)
{
	t_env	*buf;

	while (env_def)
	{
		buf = env_def;
		env_def = env_def->next;
		if (buf->env)
			free(buf->env);
		buf->env = NULL;
		if (buf->meaning)
			free(buf->meaning);
		buf->meaning = NULL;
		free(buf);
		buf = NULL;
	}
}
