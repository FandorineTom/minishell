/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 14:49:11 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/26 17:05:14 by scopycat         ###   ########.fr       */
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

void	minishell_loop2(t_command *com, char *line)
{
	while (line && *line && !com->error)
	{
		if (!com->error)
			parser(&line, com);
		start_redirect(com);
		if (!com->error)
			cmd_start(com);
		if (*line == ';' && (*(line + 1) == '\0' ||
			*(line + skip_sp(line + 1) + 1) == '\0'))
			break ;
	}
}

int		minishell_loop(t_command *com)
{
	char	*tmp;
	char	*line;

	while (1)
	{
		if (prompt_message())
			ctrl_d(com);
		if (!(get_next_line(0, &line)))
			ctrl_d(com);
		com->error = 0;
		check_mistakes(&line, com);
		tmp = line;
		save_stdin_out();
		minishell_loop2(com, line);
		return_stdin_out();
		free_all(com, 1);
		activate_pipe(NULL, NULL);
		init_com(com);
		free(tmp);
		tmp = NULL;
	}
}

int		main(int argc, char **argv, char **env)
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
