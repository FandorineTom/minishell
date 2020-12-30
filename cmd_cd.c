#include "minishell.h"
#include <stdio.h>

int		cmd_cd(t_command *com)
{
	char	pwd[1024];
	t_env	*tmp;

	getcwd(pwd, 1024);
	tmp = com->env_def;
	while (tmp)
	{
		if (!ft_strcmp("OLDPWD", tmp->env))
		{
			free(tmp->meaning);
			tmp->meaning = ft_strdup(pwd);
		}
		tmp = tmp->next;
	}
	if (chdir(com->comd->arg->arg) < 0)
		error_message(strerror(errno), -1);
	return (0);
}