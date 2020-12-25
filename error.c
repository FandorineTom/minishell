#include "minishell.h"

int     error_message(char *message, int exit_code)
{
    ft_putstr(message);
    errno = 0;
    return(exit_code);
}