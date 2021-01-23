/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:49:11 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/23 16:30:49 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		prompt_message(void)
{
	char		*path;
	int			size;

	size = 256;
	path = NULL;
	while (!(path = getcwd(NULL, size)))
	{
		size *= 2;
		if (size >= INT_MAX / 2)
			return (error_message("Not enough memory for path!", 2));
	}
	ft_putstr("minishell: ~");
	ft_putstr(path);
	ft_putstr("$ ");
	free(path);
	return (0);
}

int		minishell_loop(t_command *com)
{
	char	*tmp;
	char	*line;

	if (g_c_flag == 1)
		free_all(com, 1);
	while (1)
	{
		if (g_c_flag != 1)
			if (prompt_message())
				ctrl_d(com);
		g_c_flag = 0;
		if (!(get_next_line(0, &line)))
			ctrl_d(com);
		com->error = 0;
		check_mistakes(&line, com);
		tmp = line;
		save_stdin_out();
		while (line && *line && !com->error)
		{
			if (!com->error)
				parser(&line, com);
			start_redirect(com);
			if (!com->error)
				cmd_start(com);
			if (*line == ';' && *(line + 1) == '\0')
				break ;
		}
		return_stdin_out();
		free_all(com, 1);
		activate_pipe(NULL, NULL);
		init_com(com);
		free(tmp);
		tmp = NULL;
		// work_comman(&com);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_command	com;

	(void)argc;
	(void)argv;
	init_com(&com);
	init_env_d(&com);
	copy_env(env, &com);
	com.com_ret = 0;
	g_c_flag = 2;
	g_b_flag = 0;
	signal_handler(&com);
	minishell_loop(&com);
	free_all(&com, 0);
	return (0);
}