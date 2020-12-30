#include "minishell.h"

int		cmd_unset(t_command *com)
{
	t_env	*tmp;
	t_env	*to_del;

	tmp = com->env_def;
	while (com->env_def)
	{
		to_del = com->env_def->next;
		if (!ft_strcmp(com->comd->arg->arg, to_del->env))
		{
			free(to_del->meaning);
			free(to_del->env);
			com->env_def->next = to_del->next;
			com->env_def = tmp;
			break ;
		}
		com->env_def = com->env_def->next;
	}
	com->env_def = tmp;
	return (0);
}