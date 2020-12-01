#include "minishell.h"
#include <stdio.h>

// int		old_path(char *path)
// {
// 	if (!(g_opath = ft_strdup(path)))			// надо потом освободить память (!!!)
// 		return (0);								// обработать ошибку и очистить память
// 	return (1);
// }

int		cmd_cd(t_comd *comd)
{
	char	path[1024];							// just to check how it works

	getcwd(path, 1024);							// just to check how it works
	printf("was: %s\n", path);				// just to check how it works
	if (chdir(comd->env_var) < 0)
		error_message(strerror(errno), -1);
	getcwd(path, 1024);							// just to check how it works
	printf("now: %s\n", path);				// just to check how it works
	return (0);
}
