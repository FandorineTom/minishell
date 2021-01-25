/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:08:41 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/25 16:45:03 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	pars_double_quotes(char **line, t_command *com)
{
	size_t	len;
	char	*buf;
	char	*tmp;

	len = ft_strlen_char(*line + 1, '"');
	while (*(*line + len) == '\\')
		len = len + ft_strlen_char(*line + len + 2, '"') + 1;
	if (len == ft_strlen(*line + 1) && (*line)[len - 1] != '"')
	{
		com->comd->arg->arg = ft_substr(*line, 1, len);
		(*line) += len + 1;
	}
	else
		double_quotes_utils(com, line, len);
	if (**line != ' ')
	{
		buf = com->comd->arg->arg;
		com->comd->arg->arg = NULL;
		check_tockens(line, com);
		tmp = com->comd->arg->arg;
		com->comd->arg->arg = ft_strjoin_gnl(&buf, com->comd->arg->arg);
		free(tmp);
	}
}

int		check_open_quotes(char **line, size_t len)
{
	size_t	len_qu;
	size_t	len_qu_2;

	len_qu = ft_strlen_char(*line, '\'');
	if (len_qu != ft_strlen(*line))
		len_qu_2 = ft_strlen_char(*line + len_qu + 1, '\'');
	else
		len_qu_2 = 0;
	if (len > len_qu && len < len_qu_2)
		return (1);
	len_qu = ft_strlen_char(*line, '"');
	if (len_qu != ft_strlen(*line))
		len_qu_2 = ft_strlen_char(*line + len_qu + 1, '"');
	else
		len_qu_2 = 0;
	if (len > len_qu && len < len_qu_2)
		return (1);
	return (0);
}

void	pars_single_quotes(char **line, t_command *com)
{
	size_t	len;
	char	*buf;

	while (**line == '\'')
	{
		len = ft_strlen_char(*line + 1, '\'');
		if (len)
		{
			com->comd->arg->arg = ft_strjoin_gnl(&com->comd->arg->arg, \
				(buf = ft_substr(*line, 1, len)));
			free(buf);
		}
		(*line) += len + 2;
	}
}

void	double_quotes_utils(t_command *com, char **line, size_t len)
{
	char	*buf;

	com->comd->arg->arg = ft_strjoin_gnl(&com->comd->arg->arg, \
		(buf = ft_substr(*line, 1, len)));
	free(buf);
	if (ft_strchr(com->comd->arg->arg, '$'))
		pars_dollar(com, ft_strlen(com->comd->arg->arg));
	if (ft_strchr(com->comd->arg->arg, '\\'))
		pars_escaping(com);
	(*line) += len + 2;
}
