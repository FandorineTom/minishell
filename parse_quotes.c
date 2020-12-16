/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 14:08:41 by scopycat          #+#    #+#             */
/*   Updated: 2020/12/16 15:55:11 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pars_double_quotes(char **line, t_command *com)
{
	size_t 	len;
	size_t	len_env;
	char	*buf;
	
	len = ft_strlen_char(*line + 1, '"'); // длина от первого символа в кавычках до закрытых кавычек или до конца строки
	while (*(*line + len) == '\\') // если перед кавычкой экранирование
		len = len + ft_strlen_char(*line + len + 2, '"') + 1; // переходим на следующую кавычку
	len_env = 0;
	if (len == ft_strlen(*line + 1) && (*line)[len - 1] != '"') // если в строке нет второй кавычки
	{
		com->comd->arg->arg = ft_substr(*line, 1, len);
		(*line) += len + 1;
	}
	else // если что-то в кавычках есть
	{
		com->comd->arg->arg = ft_strjoin_gnl(com->comd->arg->arg, ft_substr(*line, 1, len));
		if (ft_strchr(com->comd->arg->arg, '$'))
			// pars_dollar(com, len);
            pars_dollar(com, ft_strlen(com->comd->arg->arg));
		if (ft_strchr(com->comd->arg->arg, '\\'))
			pars_escaping(com, len);
		(*line) += len + 2;
	}
	if (**line != ' ')
	{
		buf = com->comd->arg->arg;
        com->comd->arg->arg = NULL;
		check_tockens(line, com);
		com->comd->arg->arg = ft_strjoin_gnl(buf, com->comd->arg->arg);
	}
}