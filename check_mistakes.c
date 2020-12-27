/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mistakes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 18:49:22 by scopycat          #+#    #+#             */
/*   Updated: 2020/12/27 12:49:46 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_mistakes(char *line, t_command *com) // проверка, что ошибочный синтаксис не в кавычках
{
	size_t	i;
	size_t	len;
	size_t	len_qu;

	i = 0;
	while (*line == ' ')
		line++;
	if (*line == '|')
		i = write(2, "syntax error near unexpected token '|'\n", 39);
	if (*line == ';' && *(line + 1) == ';')
		i = write(2, "syntax error near unexpected token ';;'\n", 40);
	else if (*line == ';' && !com->comd->cmnd && !com->comd->arg)
		i = write(2, "syntax error near unexpected token ';'\n", 39);
	// len = ft_strlen(line); // вынести выяснение длины в отдельную функцию
	// if (len > ft_strlen_char(line + 1, ';') + 1)
	// 	len = ft_strlen_char(line + 1, ';') + 1;
	// if (len > ft_strlen_char(line, '>'))
	// 	len = ft_strlen_char(line, '>');
	// if (len > ft_strlen_char(line, '<'))
	// 	len = ft_strlen_char(line, '<');
	// if (len > ft_strlen_char(line, '|'))
	// 	len = ft_strlen_char(line, '|');
	// if (len > ft_strlen_char(line, '&'))
	// 	len = ft_strlen_char(line, '&');
	// len_qu = ft_strlen_char(line, '\'');
	// if (len_qu > ft_strlen_char(line, '"'))
	// 	len_qu = ft_strlen_char(line, '"');
	while (line && *line && !i)
	{
		len = find_len_to_ss(line);
		len_qu = ft_strlen_char(line, '\'');
		if (len_qu > ft_strlen_char(line, '"'))
			len_qu = ft_strlen_char(line, '"');
		if (len <= len_qu)
			line += len; // перешли на спецсимвол или на конец строки
		else
			check_mistakes_quotes(&line);
		if ((*line == '>' || *line == '<') && (*(line + 1) == '\0' || ((*(line + 1) == '>' || *(line + 1) == '<') && *(line + 2) == '\0')))
			i = write(2, "syntax error near unexpected token `newline'\n", 45);
		else
			check_mistakes_inside(&line, &i);
	}
	if (i)
		com->error = 258;
}

void	check_mistakes_quotes(char **line)
{
	size_t	len_q_one;
	size_t	i;

	i = 0;
	len_q_one = ft_strlen_char(*line, '\'');
	if (len_q_one > ft_strlen_char(*line, '"') && (i = 1))
		len_q_one = ft_strlen_char(*line, '"');
	if (i && ft_strchr(*line + len_q_one + 1, '"'))
		*line = ft_strchr(*line + len_q_one + 1, '"') + 1;
	else if (!i && ft_strchr(*line + len_q_one + 1, '\''))
		*line = ft_strchr(*line + len_q_one + 1, '\'') + 1;
}

void	check_mistakes_inside(char **line, size_t *i) // тут нужно проверять на кавычки обязательно, и если первее всего кавычки, выходить из функции снова считать
{
	size_t	len;
	size_t	len_q;

	(void)i;
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
	
	
}

size_t	find_len_to_ss(char *line)
{
	size_t	len;
	
	len = ft_strlen(line); // вынести выяснение длины в отдельную функцию
	if (len > ft_strlen_char(line + 1, ';') + 1)
		len = ft_strlen_char(line + 1, ';') + 1;
	if (len > ft_strlen_char(line, '>'))
		len = ft_strlen_char(line, '>');
	if (len > ft_strlen_char(line, '<'))
		len = ft_strlen_char(line, '<');
	if (len > ft_strlen_char(line, '|'))
		len = ft_strlen_char(line, '|');
	if (len > ft_strlen_char(line, '&'))
		len = ft_strlen_char(line, '&');
	return (len);
}