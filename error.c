#include "minishell.h"

int     error_message(char *message, int exit_code)
{
    ft_putstr_fd(message, 2);
    errno = 0;
    return(exit_code);
}

char	**error_message2(char *message)
{
    ft_putstr(message);
    errno = 0;
    return(NULL);
}

int    error_export(t_command *com)
{
    t_arg	*tmp;

    tmp = com->comd->arg;
	while (tmp)
	{
		if (!ft_isalpha(tmp->arg[0]))
		{
			ft_putstr("my_minishell: export: `");
			ft_putstr(tmp->arg);
			ft_putstr("': not a valid identifier\n");
		}
		tmp = tmp->next;
	}
    return (0);
}