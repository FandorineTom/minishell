/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_pipes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 21:48:40 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/21 14:23:17 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	activate_pipe(char **line, t_command *com)
{
	static t_comd	*new = NULL;
	static int		i = 0;

	if (!com)
	{
		new = NULL;
		i = 0;
		return ;
	}
	if (!com->comd->cmnd && !com->comd->arg)
		com->error = 1;
	if (!com->error)
	{
		com->comd->pipe_r = 1;
		if (com->comd)
			ft_comdadd_back(&new, com->comd);
		init_comd(com);
		com->comd->pipe_l = 1;
		(*line)++;
		pars_tockens(line, com);
		if ((!ft_strchr(*line, '|') || (ft_strlen_char(*line, '|') >\
			ft_strlen_char(*line, ';'))) && !i && (i = 1))
			ft_comdadd_back(&new, com->comd);
	}
	com->comd = new;
}
