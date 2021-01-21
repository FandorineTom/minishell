/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 11:13:25 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/21 14:23:26 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_env_d(t_command *com)
{
	com->env_def = (t_env*)malloc(sizeof(t_env));
	com->env_def->env = NULL;
	com->env_def->meaning = NULL;
	com->env_def->next = NULL;
}

void	init_env_def(t_env *env)
{
	env = (t_env*)malloc(sizeof(t_env));
	env->env = NULL;
	env->meaning = NULL;
	env->next = NULL;
}
