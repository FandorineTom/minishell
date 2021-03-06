/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_escaping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 21:27:32 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/25 17:11:54 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pars_esc_nq(char **line, t_command *com)
{
	size_t	len;
	char	*buf;

	while (**line && **line == '\\')
	{
		(*line)++;
		if (**line == ' ' && ((*line)++))
			com->comd->arg->arg = ft_strjoin_gnl(&com->comd->arg->arg, " ");
		else
		{
			com->comd->arg->arg = ft_strjoin_gnl(&com->comd->arg->arg, \
			(buf = ft_substr(*line, 0, 1)));
			free(buf);
			(*line)++;
		}
		len = find_len_tockens(line);
		if (len > ft_strlen_char_slash(*line, '\''))
			len = ft_strlen_char_slash(*line, '\'');
		com->comd->arg->arg = ft_strjoin_gnl(&com->comd->arg->arg, \
			(buf = ft_substr(*line, 0, len)));
		free(buf);
		*line += len;
	}
}

void	pars_escaping(t_command *com)
{
	char	*buf;
	size_t	len_slash;
	char	*tmp;
	char	*arg;

	buf = NULL;
	arg = com->comd->arg->arg;
	while (com->comd->arg->arg && *com->comd->arg->arg)
	{
		len_slash = ft_strlen_char(com->comd->arg->arg, '\\');
		tmp = ft_substr(com->comd->arg->arg, 0, len_slash);
		buf = ft_strjoin_gnl(&buf, tmp);
		com->comd->arg->arg += len_slash;
		free(tmp);
		if (*com->comd->arg->arg && *(com->comd->arg->arg + 1))
			pars_esc_inside(com, &buf);
	}
	com->comd->arg->arg = buf;
	free(arg);
}

void	pars_esc_inside(t_command *com, char **buf)
{
	char	*tmp;

	if (*(com->comd->arg->arg + 1) == '"' ||
		*(com->comd->arg->arg + 1) == '\\')
		*buf = ft_strjoin_gnl(buf, \
			(tmp = ft_substr(com->comd->arg->arg, 1, 1)));
	else
		*buf = ft_strjoin_gnl(buf, \
			(tmp = ft_substr(com->comd->arg->arg, 0, 2)));
	com->comd->arg->arg += 2;
	free(tmp);
}
