#include "minishell.h"

char	*detect_env_var(t_command *com)
{
	char	*var;
	int		i;

	i = 0;
	while(com->comd->arg->arg[i] != '=')
		i++;
	if (!(var = (char *)ft_calloc(sizeof(char), i)))
		return(error_message(strerror(errno), -1));
	i = 0;
	while (*(com->comd->arg->arg) != '=')
	{
		var[i++] = *(com->comd->arg->arg);
		com->comd->arg->arg++;
	}
	com->comd->arg->arg++;
	return (var);
}

int		cmd_export(t_command *com)
{
	t_env	*tmp;
	char	*var_tochange;

	tmp = com->env_def;
	var_tochange = detect_env_var(com);
	while (tmp->next)
	{
		if (!ft_strcmp(var_tochange, tmp->env))
		{
			
		}
		ft_putstr(tmp->env);
		ft_putchar('=');
		ft_putstr(tmp->meaning);
		ft_putchar('\n');
		tmp = tmp->next;
	}
	return (0);
}

// пытаемся смреджить все это дело....