/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_noargs.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/18 14:10:13 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/24 01:39:13 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_env	*sort_list(t_env *lst)
{
	t_env	*new_lst;
	t_env	*node;
	t_env	*cur;

	new_lst = NULL;
	while (lst)
	{
		node = lst;
		lst = lst->next;
		if (new_lst == NULL || ft_strcmp(node->env, new_lst->env) < 0)
		{
			node->next = new_lst;
			new_lst = node;
		}
		else
		{
			cur = new_lst;
			while (cur->next && ft_strcmp(node->env, cur->next->env) >= 0)
				cur = cur->next;
			node->next = cur->next;
			cur->next = node;
		}
	}
	return (new_lst);
}

t_env	*copy_env_lst(t_env *env)
{
	t_env	*tmp;
	t_env	*new;
	t_env	*buf;

	tmp = env;
	buf = (t_env*)malloc(sizeof(t_env));
	buf->env = ft_strdup(tmp->env);
	buf->meaning = ft_strdup(tmp->meaning);
	buf->next = NULL;
	tmp = tmp->next;
	while (tmp)
	{
		new = (t_env*)malloc(sizeof(t_env));
		new->env = ft_strdup(tmp->env);
		new->meaning = ft_strdup(tmp->meaning);
		new->next = NULL;
		ft_envadd_back(&buf, new);
		tmp = tmp->next;
	}
	return (buf);
}

int		cmd_export_noargs(t_command *com)
{
	t_env	*sorted;
	t_env	*tmp;

	sorted = copy_env_lst(com->env_def);
	sorted = sort_list(sorted);
	tmp = sorted;
	while (sorted)
	{
		ft_putstr("declare -x ");
		ft_putstr(sorted->env);
		if (sorted->meaning)
		{
			ft_putstr("=\"");
			ft_putstr(sorted->meaning);
			ft_putchar('"');
		}
		ft_putchar('\n');
		sorted = sorted->next;
	}
	sorted = tmp;
	free_env(sorted);
	return (0);
}
