#include "minishell.h"

int		old_path(char *path)
{
	if (!(g_opath = ft_strdup(path)))			// надо потом освободить память (!!!)
		return (0);								// обработать ошибку и очистить память
	return (1);
}

int		cmd_cd(t_comd *comd)
{
	char	path[1024];

	getcwd(path, 1024);
	ft_printf("was: %s\n", path);				// just to check how it works
	// if (!g_opath)
	// 	old_path(path);
	// if (!ft_strcmp(comd->env_var, "-"))
	// {
	// 	ft_printf("%s\n", g_opath);
	// 	chdir(g_opath);
	// 	old_path(path);
	// 	getcwd(path, 1024);						// just to check how it works
	// 	ft_printf("now: %s\n", path);				// just to check how it works
	// 	return (0);
	// }
	chdir(comd->env_var);
	getcwd(path, 1024);						// just to check how it works
	ft_printf("now: %s\n", path);				// just to check how it works
	return (0);
}
