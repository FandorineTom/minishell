#include "minishell.h"

t_env	*sort_list(t_env *lst)
{
	t_env	*new_lst;
	t_env	*node;
	t_env	*current;
	t_env	*tmp;

	new_lst = NULL;
	tmp = lst;
	while (tmp)
	{
		node = tmp;
		tmp = tmp->next;
		if (new_lst == NULL || ft_strcmp(node->env, new_lst->env) < 0)
		{
			node->next = new_lst;
			new_lst = node;
		}
		else
		{
			current = new_lst;
			while (current->next && ft_strcmp(node->env, current->next->env) >= 0)
				current = current->next;
            node->next = current->next;
            current->next = node;
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

	sorted = copy_env_lst(com->env_def);
	sorted = sort_list(sorted);
	while (sorted)
	{
		ft_putstr("declare -x ");
		ft_putstr(sorted->env);
		ft_putstr("=\"");
		ft_putstr(sorted->meaning);
		ft_putchar('"');
		ft_putchar('\n');
		sorted = sorted->next;
	}
	free_env(sorted);
	return (0);
}