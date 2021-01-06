/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:29:32 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/06 21:50:58 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_redirect(char **line, t_command *com) // дописать
{
	t_arg	*new;
	t_redir	*tmp;
	t_arg	*buf;
	static size_t	i = 0;

	if (!i++)
		tmp = NULL;
	else
		tmp = com->comd->redir;
	new = com->comd->arg;
	while (new && new->next) // докручиваем до последнего элемента, чтобы знать, какой следующий и какой файл нам нужен
		new = new->next;
	while (line && *line && **line && **line != ';' && **line != '|')
	{
		init_redirect(com);
		if (**line == '>' && *(*line + 1) == '>')
		{
			fill_redirect(com, 3);
			(*line) += 2;
		}
		else if (**line == '>' && *(*line + 1) != '>' && *(*line + 1) != '<')
		{
			fill_redirect(com, 1);
			(*line)++;
		}
		else if (**line == '<' && *(*line + 1) == '>')
		{
			fill_redirect(com, 4);
			(*line) += 2;
		}
		if (com->comd->redir->type_red)
			ft_redadd_back(&tmp, com->comd->redir);
		// com->comd->redir = tmp;
		// check_tockens(line, com);
		pars_tockens(line, com);
		buf = com->comd->arg;
		while (buf && buf->previous != new)
			buf = buf->next;
		// while (tmp->next)
		// 	tmp = tmp->next;
		if (buf->previous == new && buf)
		{
			com->comd->redir->file_name = ft_strdup(buf->arg);
			// tmp->file_name = ft_strdup(buf->arg);
			ft_argdel_list(&buf);
		}
		// if (tmp->previous)
		// 	tmp = tmp->previous;
		// if (com->comd->redir->type_red)
		// 	ft_redadd_back(&tmp, com->comd->redir);
		// com->comd->redir = tmp;
	}
	com->comd->redir = tmp;
}

void	pars_reverse_redirect(char **line, t_command *com)
{
	fill_redirect(com, 2);
	// t_redir	*tmp;

	// com->comd->redir->type_red = 2;
	// com->comd->redir->r_redir = 1;
	// if (!com->comd->redir)
	// 	init_redirect(com);
	// com->comd->redir->l_redir = 1;
	// com->comd->redir->previous = tmp;
	// com->comd->redir = com->comd->redir->previous;
	// и нужно в следующий лист comd запихнуть, что там есть левый редирект
	(*line)++;
}

void	fill_redirect(t_command *com, size_t type_r)
{
	t_redir	*tmp;

	com->comd->redir->type_red = type_r;
	com->comd->redir->r_redir = 1;
	tmp = com->comd->redir;
	com->comd->redir = com->comd->redir->next;
	if (!com->comd->redir)
		init_redirect(com);
	com->comd->redir->l_redir = 1; // это не работает
	com->comd->redir->previous = tmp;
	com->comd->redir = com->comd->redir->previous;
	tmp = NULL;
}