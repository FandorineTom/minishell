/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 18:40:09 by scopycat          #+#    #+#             */
/*   Updated: 2020/12/08 15:29:22 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_command *com, int i)
{
	(void)i;
	free_comd(com->comd);
	// free_arg(com->arg);
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
		free_arg(buf->arg);
		if (buf->env_var)
			free(buf->env_var);
		buf->env_var = NULL;
		free(buf);
		buf = NULL;
	}
	
	// buf = comd;
	// while (buf)
	// {
	// 	while(buf->next)
	// 		buf = buf->next;
	// 	if (buf->cmnd)
	// 		free(buf->cmnd);
	// 	buf->cmnd = NULL;
	// 	free_flag(buf->flag);
	// 	if (buf->env_var)
	// 		free(buf->env_var);
	// 	buf->env_var = NULL;
	// 	free(buf);
	// 	buf = comd;
	// 	if (!buf->next)
	// 		buf = NULL;
	// }
	// comd = NULL;
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
		free(buf);
		buf = NULL;
	}	
	// buf = flag;
	// while (buf)
	// {
	// 	while(buf->next)
	// 		buf = buf->next;
	// 	if (buf->flag)
	// 		free(buf->flag);
	// 	buf->flag = NULL;
	// 	free(buf);
	// 	buf = flag;
	// 	if (!buf->next)
	// 		buf = NULL;
	// }
	// flag = NULL;
}

void 	free_arg(t_arg *arg)
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
		free_pipe(buf->pipes);
		free(buf);
		buf = NULL;
	}
}

void	free_pipe(t_pipe *pipes)
{
	t_pipe	*buf;

	while (pipes)
	{
		buf = pipes;
		pipes = pipes->next;
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
	// buf = env_def;
	// while (buf)
	// {
	// 	while (buf->next)
	// 		buf = buf->next;
	// 	if (buf->env)
	// 		free(buf->env);
	// 	buf->env = NULL;
	// 	if (buf->meaning)
	// 		free(buf->meaning);
	// 	buf->meaning = NULL;
	// 	free(buf);
	// 	buf = env_def;
	// 	if (!buf->next)
	// 		buf = NULL;
	// }
	// env_def = NULL;
}