/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_redirect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:29:32 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/25 16:43:08 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pars_redirect(char **line, t_command *com)
{
	t_arg	*new;
	t_redir	*tmp;
	int		i;

	tmp = com->comd->redir;
	new = com->comd->arg;
	i = 1;
	while (new && new->next && (i++))
		new = new->next;
	if (i == 1 && new && !new->arg)
		i = 0;
	while (line && *line && **line && **line != ';' && **line != '|')
	{
		which_redirect(line, com);
		if (com->comd->redir->type_red)
			ft_redadd_back(&tmp, com->comd->redir);
		pars_tockens(line, com);
		fill_file_name(com, i, new);
	}
	com->comd->redir = tmp;
}

void	fill_redirect(t_command *com, size_t type_r)
{
	com->comd->redir->type_red = type_r;
	com->comd->redir->r_redir = 1;
}

void	which_redirect(char **line, t_command *com)
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
}

void	fill_file_name(t_command *com, int i, t_arg *new)
{
	t_arg	*buf;

	while (com->comd && com->comd->next &&
		com->comd->next->redir->type_red &&
		!com->comd->next->redir->file_name)
		com->comd = com->comd->next;
	buf = com->comd->arg;
	while (buf && buf->previous != new && i && buf->next)
		buf = buf->next;
	if ((buf->previous == new || !i) && buf && buf->arg)
	{
		com->comd->redir->file_name = ft_strdup(buf->arg);
		ft_argdel_list(&buf);
	}
	if (!i)
		com->comd->arg = buf;
}
