/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tocken_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/21 13:41:35 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/24 11:40:51 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	if (*(*line + 1) && len > ft_strlen_char(*line + 1, '"') + 1 &&
		!check_open_quotes(line, \
		ft_strlen_char(*line + 1, '"') + 1))
		len = ft_strlen_char(*line + 1, '"') + 1;
	return (find_len_tockens_2(len, line));
}

size_t		find_len_tockens_2(size_t len, char **line)
{
	if (*(*line + 1) && len > ft_strlen_char(*line + 1, '\'') + 1 &&
		!check_open_quotes(line, \
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
