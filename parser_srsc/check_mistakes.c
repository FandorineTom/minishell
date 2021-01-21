/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mistakes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 18:49:22 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/21 14:23:34 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_mistakes(char **line_true, t_command *com)
{
	size_t	i;
	char	*line;

	i = 0;
	line = *line_true;
	while (*line == ' ')
		line++;
	if (*line == '|')
		i = write(2, "syntax error near unexpected token '|'\n", 39);
	if (*line == '&')
		i = write(2, "syntax error near unexpected token '&'\n", 39);
	if (*line == ';' && *(line + 1) == ';')
		i = write(2, "syntax error near unexpected token ';;'\n", 40);
	else if (*line == ';')
		i = write(2, "syntax error near unexpected token ';'\n", 39);
	while (line && *line && !i)
		check_line_mistakes(&line, &i, line_true, com);
	if (i)
		com->error = 258;
}

void	check_line_mistakes(char **line, size_t *i, char **line_true, \
								t_command *com)
{
	size_t	len;
	size_t	len_qu;

	len = find_len_to_ss(*line);
	len_qu = ft_strlen_char_slash(*line, '\'');
	if (len_qu > ft_strlen_char_slash(*line, '"'))
		len_qu = ft_strlen_char_slash(*line, '"');
	if (len <= len_qu)
		*line += len;
	else
		check_mistakes_quotes(line);
	if (((**line == '>' || **line == '<') && (*(*line + 1) == '\0')) ||
		((*(*line + 1) == '>' || *(*line + 1) == '<') &&
		*(*line + 2) == '\0') || ((**line == '>' || **line == '<') &&
		(*(*line + skip_sp(*line + 1) + 1) == '\0')) ||
		((*(*line + 1) == '>' || *(*line + 1) == '<') &&
		*(*line + skip_sp(*line + 2) + 2) == '\0'))
		*i = write(2, "syntax error near unexpected token `newline'\n", 45);
	else if (**line == '>' && *(*line + 1) == '|')
		rewrite_line(line_true, line);
	else
		check_mistakes_inside(line, i, line_true, com);
}

void	check_mistakes_quotes(char **line)
{
	size_t	len_q_one;
	size_t	i;

	i = 0;
	len_q_one = ft_strlen_char_slash(*line, '\'');
	if (len_q_one > ft_strlen_char_slash(*line, '"') && (i = 1))
		len_q_one = ft_strlen_char_slash(*line, '"');
	if (i && ft_strchr(*line + len_q_one + 1, '"'))
		*line = ft_strchr(*line + len_q_one + 1, '"') + 1;
	else if (!i && ft_strchr(*line + len_q_one + 1, '\''))
		*line = ft_strchr(*line + len_q_one + 1, '\'') + 1;
}

void	check_mistakes_inside(char **line, size_t *i, char **line_true, \
								t_command *com)
{
	size_t	len;
	size_t	len_q;

	while (**line == ' ')
		(*line)++;
	len = find_len_to_ss(*line);
	len_q = ft_strlen_char(*line, '\'');
	if (len_q > ft_strlen_char(*line, '"'))
		len_q = ft_strlen_char(*line, '"');
	if (len > len_q)
		return ;
	else if (len > 1)
		*line += len;
	if (**line == ';' && *(*line + 1) == '|')
		*i = write(2, "syntax error near unexpected token '|'\n", 39);
	if (**line == ';' && *(*line + 1) == ';')
		*i = write(2, "syntax error near unexpected token ';;'\n", 40);
	if (**line == '<' && *(*line + 1) == '|')
		*i = write(2, "syntax error near unexpected token '|'\n", 39);
	if (**line == '|' && *(*line + 1) == '|')
		*i = write(2, "syntax error near unexpected token '||'\n", 40);
	if (**line == '&' && *(*line + 1) == '&')
		*i = write(2, "syntax error near unexpected token '&'\n", 39);
	if (!(*i))
		check_multyline(line, i, line_true, com);
}

void	check_multyline(char **line, size_t *i, char **line_true, \
								t_command *com)
{
	if ((**line == '|' && *(*line + 1) == '\0' && ((*line)++)) ||
		((**line == '|' && *(*line + skip_sp(*line + 1) + 1) == '\0' &&
		((*line) + skip_sp(*line + 1) + 1))))
		please_enter(line_true, i, com);
	else
	{
		(*line)++;
		while (**line == ' ')
			(*line)++;
		if (!(*i) && **line == '|')
			*i = write(2, "syntax error near unexpected token '|'\n", 39);
		if (!(*i) && **line == '&')
			*i = write(2, "syntax error near unexpected token '&'\n", 39);
		if (!(*i) && **line == ';')
			*i = write(2, "syntax error near unexpected token ';'\n", 39);
	}
}
