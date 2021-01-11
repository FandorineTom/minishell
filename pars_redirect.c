/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:29:32 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/09 18:03:53 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_redirect(char **line, t_command *com)
{
	t_arg	*new;
	t_redir	*tmp;
	t_arg	*buf;
	int		i;

	tmp = com->comd->redir;
	new = com->comd->arg;
	i = 1;
	while (new && new->next && (i++)) // докручиваем до последнего элемента, чтобы знать, какой следующий и какой файл нам нужен
		new = new->next;
	if (i == 1 && new && !new->arg)
		i = 0;
	while (line && *line && **line && **line != ';' && **line != '|')
	{
		if (com->comd->redir && com->comd->redir->r_redir)
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
		else if (**line == '<' && *(*line + 1) != '>')
		{
			fill_redirect(com, 2);
			(*line) += 1;
		}
		if (com->comd->redir->type_red)
			ft_redadd_back(&tmp, com->comd->redir);
		pars_tockens(line, com);
		buf = com->comd->arg;
		while (buf && buf->previous != new && i)
			buf = buf->next;
		if ((buf->previous == new || !i) && buf && buf->arg)
		{
			com->comd->redir->file_name = ft_strdup(buf->arg);
			ft_argdel_list(&buf);
		}
		if (!i)
			com->comd->arg = buf;
	}
	com->comd->redir = tmp;
}

// void	pars_reverse_redirect(char **line, t_command *com)
// {
// 	fill_redirect(com, 2);
// 	(*line)++;
// }

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