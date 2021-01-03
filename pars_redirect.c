/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:29:32 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/03 11:31:09 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_redirect(char **line, t_command *com) // дописать
{
	t_arg	*new;
	t_redir	*tmp;
	t_arg	*buf;

	tmp = NULL;
	new = com->comd->arg;
	while (new->next) // докручиваем до последнего элемента, чтобы знать, какой следующий и какой файл нам нужен
		new = new->next;
	while (line && *line && **line && **line != ';' && **line != '|')
	{
		init_redirect(com);
		if (**line == '>' && *(*line + 1) == '>')
		{
			com->comd->redir->type_red = 3;
			com->comd->redir->r_redir = 1;
		// и нужно в следующий лист comd запихнуть, что там есть левый редирект
			(*line) += 2;
		}
		else if (**line == '>' && *(*line + 1) != '>' && *(*line + 1) != '<')
		{
			com->comd->redir->type_red = 1;
			com->comd->redir->r_redir = 1;
			// и нужно в следующий лист comd запихнуть, что там есть левый редирект
			(*line)++;
		}
		else if (**line == '<' && *(*line + 1) == '>')
		{
			com->comd->redir->type_red = 4;
			com->comd->redir->r_redir = 1;
			// и нужно в следующий лист comd запихнуть, что там есть левый редирект
			(*line) += 2;
		}
		check_tockens(line, com);
		buf = com->comd->arg;
		while (buf && buf->previous != new)
			buf = buf->next;
		if (buf->previous == new)
		{
			com->comd->redir->file_name = ft_strdup(com->comd->arg->arg);
			
		}
		if (com->comd->redir->type_red)
			ft_redadd_back(&tmp, com->comd->redir);
	}
	com->comd->redir = tmp;
}

void	pars_reverse_redirect(char **line, t_command *com)
{
	com->comd->redir->type_red = 2;
	com->comd->redir->r_redir = 1;
	// и нужно в следующий лист comd запихнуть, что там есть левый редирект
	(*line)++;
}