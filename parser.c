/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:32:31 by scopycat          #+#    #+#             */
/*   Updated: 2020/11/10 19:42:09 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(char *line, t_command *com)
{
	pars_pipes(line, com);
	pars_commands(line, com);
	// pars_variables(blocks, com);
}

void	pars_pipes(char *line, t_command *com)
{
	while (line && *line)
	{
		if (*line == '|')
			com->pipe_count++;
		(*line)++;
	}
	com->no_command = com->pipe_count + 1;
	com->no_arg = com->pipe_count + 1;
}

void	pars_commands(char *line, t_command *com)
{
	size_t	i;
	t_comd	*new;

	i = 0;
	new = com->comd;
	while (line && line[i])
	{
		// pars_block(blocks[i]);
		i++;
		com->comd = com->comd->next;
		init_comd(com);
	}
	com->comd = new;
}