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
			ft_putstr_fd("our_minishell_almost_work: export: `", 2);
			ft_putstr_fd(tmp->arg, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		tmp = tmp->next;
	}
    return (1);
}