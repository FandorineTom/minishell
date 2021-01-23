/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tockens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/03 11:30:57 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/23 16:47:04 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pars_tockens(char **line, t_command *com)
{
	t_arg			*new;

	new = com->comd->arg;
	skip_spaces(line);
	com->comd->no_command = check_command(line, com);
	if (com->env_var && !com->comd->no_command)
	{
		com->comd->arg->arg = ft_strdup(com->env_var);
		free(com->env_var);
		com->env_var = NULL;
		while (**line && **line != ' ' && **line != ';' && **line != '|' &&
		**line != '>' && **line != '<')
			check_tockens_ss(line, com);
		ft_argadd_back(&new, com->comd->arg);
	}
	skip_spaces(line);
	while (line && *line && **line && **line != ';' && **line != '|' &&
			**line != '>' && **line != '<')
		pars_tockens_2(com, line, new);
	com->comd->arg = new;
	if (**line == '|')
		activate_pipe(line, com);
	if (**line == '>' || **line == '<')
		pars_redirect(line, com);
}

void	pars_tockens_2(t_command *com, char **line, t_arg *new)
{
	char	*tmp;
	char	*buf;

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
		buf = com->comd->arg->arg;
		com->comd->arg->arg = ft_strjoin_gnl(&tmp, com->comd->arg->arg);
		free(buf);
	}
	if (com->comd->arg->arg)
		ft_argadd_back(&new, com->comd->arg);
	skip_spaces(line);
}

void	check_tockens(char **line, t_command *com)
{
	size_t	len;
	char	*buf;

	skip_spaces(line);
	if (!(len = find_len_tockens(line)))
		com->comd->arg->no_arg = 0;
	else if (**line != '|' && **line != '"' && **line != '\'' &&
		**line != '\\' && **line != '>' && **line != '<')
	{
		com->comd->arg->arg = ft_strjoin_gnl(&com->comd->arg->arg, \
			(buf = ft_substr(*line, 0, len)));
		(*line) += len;
		free(buf);
	}
	check_tockens_ss(line, com);
	if (**line && **line != ' ' && **line != ';' && **line != '|' &&
		**line != '>' && **line != '<')
		check_tockens(line, com);
}

void	check_tockens_ss(char **line, t_command *com)
{
	if (**line == '"')
		pars_double_quotes(line, com);
	if (**line == '\'')
		pars_single_quotes(line, com);
	if (**line == '\\')
		pars_esc_nq(line, com);
	if (**line == '$')
	{
		check_env_var(line, com);
		change_env_var_meaning(com);
		com->comd->arg->arg = ft_strjoin_gnl(&com->comd->arg->arg, \
			com->env_var);
		free(com->env_var);
		com->env_var = NULL;
	}
}
