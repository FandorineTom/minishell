/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_structs_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 20:09:29 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/13 17:58:36 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*bonus;

	if (!new || !lst)
		return ;
	bonus = *lst;
	if (bonus && *lst != new)
	{
		while (bonus->next)
			bonus = bonus->next;
		bonus->next = new;
		new->next = NULL;
	}
	else
		*lst = new;
}

void	ft_argadd_back(t_arg **lst, t_arg *new)
{
	t_arg	*bonus;
	t_arg	*buf;

	if (!new || !lst)
		return ;
	bonus = *lst;
	if (bonus && *lst != new)
	{
		while (bonus->next)
		{
			buf = bonus;
			bonus = bonus->next;
			bonus->previous = buf;
		}
		bonus->next = new;
		new->previous = bonus;
		new->next = NULL;
	}
	else
		*lst = new;
}

void	ft_comdadd_back(t_comd **lst, t_comd *new)
{
	t_comd	*bonus;
	t_comd	*buf;

	if (!new || !lst)
		return ;
	bonus = *lst;
	if (bonus && *lst != new)
	{
		while (bonus->next)
		{
			buf = bonus;
			bonus = bonus->next;
			bonus->previous = buf;
		}
		bonus->next = new;
		new->previous = bonus;
		new->next = NULL;
	}
	else
		*lst = new;
}

void	ft_redadd_back(t_redir **lst, t_redir *new)
{
	t_redir	*bonus;
	t_redir	*buf;

	if (!new || !lst)
		return ;
	bonus = *lst;
	if (bonus && *lst != new)
	{
		while (bonus->next)
		{
			buf = bonus;
			bonus = bonus->next;
			bonus->previous = buf;
			
		}
		bonus->next = new;
		new->previous = bonus;
		new->next = NULL;
	}
	else
		*lst = new;
}

void	ft_argdel_list(t_arg **old)
{
	t_arg	*nxt;
	t_arg	*prvs;

	prvs = (*old)->previous;
	nxt = (*old)->next;
	if (prvs)
		prvs->next = nxt;
	if (nxt)
		nxt->previous = prvs;
	if ((*old)->arg)
		free((*old)->arg);
	(*old)->arg = NULL;
	free(*old);
	if (prvs)
		*old = prvs;
	else
		*old = nxt;
}