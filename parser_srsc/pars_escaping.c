/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_escaping.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 21:27:32 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/21 19:07:06 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pars_esc_nq(char **line, t_command *com)
{
	size_t	len;

	while (**line && **line == '\\')
	{
		(*line)++;
		if (**line == ' ' && ((*line)++))
			com->comd->arg->arg = ft_strjoin_gnl(com->comd->arg->arg, " ");
		else
		{
			com->comd->arg->arg = ft_strjoin_gnl(com->comd->arg->arg, \
			ft_substr(*line, 0, 1));
			(*line)++;
		}
		len = find_len_tockens(line);
		if (len > ft_strlen_char_slash(*line, '\''))
			len = ft_strlen_char_slash(*line, '\'');
		// len = ft_strlen_space(*line);
		// if (len > ft_strlen_char(*line + 1, '\\') + 1)
		// 	len = ft_strlen_char(*line + 1, '\\') + 1;
		com->comd->arg->arg = ft_strjoin_gnl(com->comd->arg->arg, \
			ft_substr(*line, 0, len));
		*line += len;
	}
}

void	pars_escaping(t_command *com, size_t len_str)
{
	char	*buf;
	size_t	len_slash;

	buf = NULL;
	(void)len_str;
	while (com->comd->arg->arg && *com->comd->arg->arg)
	{
		len_slash = ft_strlen_char(com->comd->arg->arg, '\\');
		buf = ft_strjoin_gnl(buf, ft_substr(com->comd->arg->arg, 0, len_slash));
		com->comd->arg->arg += len_slash;
		if (*com->comd->arg->arg && *(com->comd->arg->arg + 1))
		{
			if (*(com->comd->arg->arg + 1) == '"' ||
				*(com->comd->arg->arg + 1) == '\\')
				buf = ft_strjoin_gnl(buf, ft_substr(com->comd->arg->arg, 1, 1));
			else
				buf = ft_strjoin_gnl(buf, ft_substr(com->comd->arg->arg, 0, 2));
			com->comd->arg->arg += 2;
		}
	}
	com->comd->arg->arg = buf;
}
