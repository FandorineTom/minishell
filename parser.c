/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:32:31 by scopycat          #+#    #+#             */
/*   Updated: 2020/11/15 17:10:31 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(char **line, t_command *com)
{
	pars_pipes(line, com);
	while (line && *line && **line && (**line != ';' || !com->quotes_op))
		pars_tockens(line, com);
	// pars_variables(blocks, com);
}

void	pars_pipes(char **line, t_command *com)
{
	while (line && *line && **line)
	{
		if (**line == '|')
			com->pipe_count++;
		**line++;
	}
	com->no_command = com->pipe_count + 1;
	com->no_arg = com->pipe_count + 1;
}

void	pars_tockens(char **line, t_command *com)
{
	t_comd	*new;

	new = com->comd;
	while (line && *line && **line && (**line != ';' || !com->quotes_op))
	{
		pars_command(line, com);
		pars_flags(line, com);
		pars_variables(line, com);
		*line++;
		com->comd = com->comd->next;
		init_comd(com);
	}
	com->comd = new;
}
