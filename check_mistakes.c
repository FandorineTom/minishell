/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_mistakes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/23 18:49:22 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/02 18:56:48 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_mistakes(char **line_true, t_command *com) // проверка, что ошибочный синтаксис не в кавычках
{
	size_t	i;
	size_t	len;
	size_t	len_qu;
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
	// else if (*line == ';' && !com->comd->cmnd && !com->comd->arg)
		i = write(2, "syntax error near unexpected token ';'\n", 39);
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
		else if (*line == '>' && *(line + 1) == '|')
			rewrite_line(line_true, &line);
			// line += 2;
		else
			check_mistakes_inside(&line, &i, line_true, com);
	}
	if (i)
		com->error = 258;
}

void	rewrite_line(char **line_true, char **line)
{
	char *buf;
	char *buf2;
	
	buf2 = ft_strdup(*line + 2);
	buf = ft_substr(*line_true, 0, ft_strlen(*line_true) - ft_strlen(*line) + 1);
	free(*line_true);
	*line_true = ft_strjoin_gnl(buf, buf2);
	free(buf2);
	buf2 = NULL;
	*line += 2;
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

void	check_mistakes_inside(char **line, size_t *i, char **line_true, t_command *com) // тут нужно проверять на кавычки обязательно, и если первее всего кавычки, выходить из функции снова считать
{
	size_t	len;
	size_t	len_q;
	char	sym;

	(void)i;
	sym = **line;
	len = find_len_to_ss(*line);
	len_q = ft_strlen_char(*line, '\'');
	if (len_q > ft_strlen_char(*line, '"'))
		len_q = ft_strlen_char(*line, '"');
	if (len > len_q)
		return ;
	else if (len > 1)
		*line += len;
	if (**line == ';' && *(*line + 1) == '|') // нужны эти проверки, и если между этими символами пробелы
		*i = write(2, "syntax error near unexpected token '|'\n", 39);
	if (**line == ';' && *(*line + 1) == ';')
		*i = write(2, "syntax error near unexpected token ';;'\n", 40);
	if (**line == '<' && *(*line + 1) == '|')
		*i = write(2, "syntax error near unexpected token '|'\n", 39);
	if (**line == '|' && *(*line + 1) == '|')
		*i = write(2, "syntax error near unexpected token '||'\n", 40);
	if (**line == '&' && *(*line + 1) == '&')
		*i = write(2, "syntax error near unexpected token '&'\n", 39);
	if ((**line == '|' && *(*line + 1) == '\0' && ((*line)++)) || 
	((**line == '|' && *(*line + skip_sp(*line + 1) + 1) == '\0' && ((*line) + skip_sp(*line + 1) + 1))))
		please_enter(line_true, i, com);
	// else if (sym != ';')
	// 	(*line)++; 
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
	// (*line)++;
	// while (**line == ' ')
	// 	(*line)++;
	// if (!(*i) && **line == '|')
	// 	*i = write(2, "syntax error near unexpected token '|'\n", 39);
	// if (!(*i) && **line == '&')
	// 	*i = write(2, "syntax error near unexpected token '&'\n", 39);
	// if (!(*i) && **line == ';')
	// 	*i = write(2, "syntax error near unexpected token ';'\n", 39);
}

	
size_t	skip_sp(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (i);	
}


void	please_enter(char **line_true, size_t *i, t_command *com)
{
	char	*line;
	char	*tmp;
	char	*tmp2;
	
	(void)com;
	(void)i;
	write(1, "please enter: ", 14);
	get_next_line(0, &line);
	tmp = ft_strdup(" ");
	tmp2 = line;
	line = ft_strjoin_gnl(tmp, tmp2);
	free(tmp2);
	*line_true = ft_strjoin_gnl(*line_true, line);
	check_mistakes_inside(&line, i, line_true, com);
	// check_mistakes(line_true, com);
}

size_t	find_len_to_ss(char *line)
{
	size_t	len;
	
	len = ft_strlen(line); // вынести выяснение длины в отдельную функцию
	if (len > ft_strlen_char(line, ';'))
		len = ft_strlen_char(line, ';');
	// if (len > ft_strlen_char(line + 1, ';') + 1)
	// 	len = ft_strlen_char(line + 1, ';') + 1;
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