/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:32:31 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/23 16:49:39 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	parser(char **line, t_command *com)
{
	if (**line == ';')
	{
		(*line)++;
		free_all(com, 1);
		init_com(com);
		activate_pipe(line, NULL);
	}
	skip_spaces(line);
	while (line && *line && **line && **line != ';')
	{
		pars_tockens(line, com);
		while (com->comd && com->comd->next)
		{
			check_result(com);
			com->comd = com->comd->next;
		}
		check_result(com);
		while (com->comd->previous)
			com->comd = com->comd->previous;
	}
	write(1, "end of parser\n", 14); // чисто для теста, потом нужно убрать
}

void	check_result(t_command *com)
{
	t_arg	*new;

	new = com->comd->arg;
	if (new && !new->arg)
		new = new->next;
	if (com->comd->cmnd)
		com->comd->no_command = 1;
	if (!com->comd->no_command && new && new->arg)
		check_result_utils(com, new);
	else if (!com->comd->flag->flag && new && new->arg)
		check_result_flag(com, new);
	while (com->comd->arg && com->comd->arg->next)
	{
		if (com->comd->arg && (com->comd->arg->next ||
			com->comd->arg->previous) && com->comd->arg->arg &&
			!com->comd->arg->arg[0])
			ft_argdel_list(&com->comd->arg);
		if (com->comd->arg->next)
			com->comd->arg = com->comd->arg->next;
	}
	while (com->comd->arg && com->comd->arg->previous)
		com->comd->arg = com->comd->arg->previous;
}

void	check_result_utils(t_command *com, t_arg *new)
{
	if (!(ft_strncmp(new->arg, "echo\0", 5)) || !(ft_strncmp(new->arg, \
		"cd\0", 3)) || !(ft_strncmp(new->arg, "pwd\0", 4)) || !(ft_strncmp(\
		new->arg, "export\0", 7)) || !(ft_strncmp(new->arg, "unset\0", 6)) ||
		!(ft_strncmp(new->arg, "env\0", 5)) ||
		!(ft_strncmp(new->arg, "exit\0", 5)))
	{
		com->comd->cmnd = ft_strdup(new->arg);
		com->comd->arg = com->comd->arg->next;
		if (com->comd->arg)
			com->comd->arg->previous = NULL;
		if (new->arg)
			free(new->arg);
		free(new);
		new = com->comd->arg;
		com->comd->no_command = 1;
		check_result_flag(com, new);
	}
}

void	check_result_flag(t_command *com, t_arg *new)
{
	while (new && new->arg && !(ft_strncmp(new->arg, "-n\0", 3)))
	{
		com->comd->flag->flag = ft_strdup(new->arg);
		com->comd->flag->no_flag = 1;
		com->comd->arg = com->comd->arg->next;
		com->comd->arg->previous = NULL;
		free(new);
		new = com->comd->arg;
	}
}
