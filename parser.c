/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 22:32:31 by scopycat          #+#    #+#             */
/*   Updated: 2020/11/09 11:52:54 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(char *line, t_command *com)
{
	(void)line;
	(void)com;
	pars_pipes(line, com);
	pars_commands(&line, com);
	pars_variables(&line, com);
}

void	pars_pipes(char *line, t_command *com)
{
	while (line && *line)
	{
		if (*line == '|')
			com->pipe_count++;
		(*line)++;
	}
}

void	pars_commands(char **line, t_command *com)
{
	
}