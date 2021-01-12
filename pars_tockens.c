/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tockens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:30:57 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/13 00:50:00 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_tockens(char **line, t_command *com)
{
	t_arg			*new;
	char			*tmp;

	new = com->comd->arg;
	while (**line == ' ')
		(*line)++;
	com->comd->no_command = check_command(line, com);
	if (com->env_var && !com->comd->no_command)
	{
		init_arg(com);
		com->comd->arg->arg = ft_strdup(com->env_var);
		free(com->env_var);
		com->env_var = NULL;
		ft_argadd_back(&new, com->comd->arg);
	}
	while (**line == ' ')
		(*line)++;
	while (line && *line && **line && **line != ';' && **line != '|' &&
			**line != '>' && **line != '<')
	{
		if (com->comd->arg && com->comd->arg->arg)
			init_arg(com);
		if (!check_env_var(line, com))
			com->no_var = 0;
		if (!com->no_var)
			check_tockens(line, com);
		else
			change_env(com);
		if (**line == '$' && com->comd->arg && com->comd->arg->arg)
		{
			tmp = com->comd->arg->arg;	
			check_env_var(line, com);
			change_env(com);
			com->comd->arg->arg = ft_strjoin_gnl(tmp, com->comd->arg->arg);
		}
		if (com->comd->arg->arg)
			ft_argadd_back(&new, com->comd->arg);
		while (**line == ' ')
			(*line)++;
	}
	com->comd->arg = new;
	if (**line == '|')
		activate_pipe(line, com);
	if (**line == '>' || **line == '<')
		pars_redirect(line, com);
	// if (**line == '<')
	// 	pars_reverse_redirect(line, com);
}

void	check_tockens(char **line, t_command *com)
{
	size_t	len;

	while (**line == ' ')
		(*line)++;
	if (!(len = find_len_tockens(line)))
		com->comd->arg->no_arg = 0;
	else if (**line != '|' && **line != '"' && **line != '\'' &&
		**line != '\\' && **line != '>' && **line != '<')
	{
		com->comd->arg->arg = ft_strjoin_gnl(com->comd->arg->arg, \
			ft_substr(*line, 0, len));
		(*line) += len;
	}
	if (**line == '"')
		pars_double_quotes(line, com);
	if (**line == '\'')
		pars_single_quotes(line, com);
	else if (**line == '\\')
		pars_esc_nq(line, com);
	if (**line == '$')
	{
		check_env_var(line, com);
		change_env_var_meaning(com);
		com->comd->arg->arg = ft_strjoin_gnl(com->comd->arg->arg, com->env_var);
	}
	if (**line && **line != ' ' && **line != ';' && **line != '|' && **line != '>' && **line != '<')
		check_tockens(line, com);
}

size_t		find_len_tockens(char **line)
{
	size_t	len;

	len = ft_strlen_space(*line);
	if (len > ft_strlen_char(*line, ';') && !check_open_quotes(line, \
		ft_strlen_char(*line, ';')))
		len = ft_strlen_char(*line, ';');
	if (len > ft_strlen_char(*line, '$') && !check_open_quotes(line, \
		ft_strlen_char(*line, '$')))
		len = ft_strlen_char(*line, '$');
	if (len > ft_strlen_char(*line + 1, '"') + 1 && !check_open_quotes(line, \
		ft_strlen_char(*line + 1, '"') + 1))
		len = ft_strlen_char(*line + 1, '"') + 1;
	if (len > ft_strlen_char(*line + 1, '\'') + 1 && !check_open_quotes(line, \
		ft_strlen_char(*line + 1, '\'') + 1))
		len = ft_strlen_char(*line + 1, '\'') + 1;
	if (len > ft_strlen_char(*line, '>') && !check_open_quotes(line, \
		ft_strlen_char(*line, '>')))
		len = ft_strlen_char(*line, '>');
	if (len > ft_strlen_char(*line, '<') && !check_open_quotes(line, \
		ft_strlen_char(*line, '<')))
		len = ft_strlen_char(*line, '<');
	if (len > ft_strlen_char(*line, '\\') && !check_open_quotes(line, \
		ft_strlen_char(*line, '\\')))
		len = ft_strlen_char(*line, '\\');
	if (len > ft_strlen_char(*line, '|') && !check_open_quotes(line, \
		ft_strlen_char(*line, '|')))
		len = ft_strlen_char(*line, '|');
	return (len);
}