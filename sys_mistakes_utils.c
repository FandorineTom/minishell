/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sys_mistakes_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 19:08:15 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/02 19:14:25 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rewrite_line(char **line_true, char **line)
{
	char *buf;
	char *buf2;

	buf2 = ft_strdup(*line + 2);
	buf = ft_substr(*line_true, 0, ft_strlen(*line_true) - \
			ft_strlen(*line) + 1);
	free(*line_true);
	*line_true = ft_strjoin_gnl(buf, buf2);
	free(buf2);
	buf2 = NULL;
	*line += 2;
}

size_t	skip_sp(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (i);
}

size_t	find_len_to_ss(char *line)
{
	size_t	len;

	len = ft_strlen(line);
	if (len > ft_strlen_char(line, ';'))
		len = ft_strlen_char(line, ';');
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

void	please_enter(char **line_true, size_t *i, t_command *com)
{
	char	*line;
	char	*tmp;
	char	*tmp2;

	write(1, "please enter: ", 14);
	get_next_line(0, &line);
	tmp = ft_strdup(" ");
	tmp2 = line;
	line = ft_strjoin_gnl(tmp, tmp2);
	free(tmp2);
	*line_true = ft_strjoin_gnl(*line_true, line);
	check_mistakes_inside(&line, i, line_true, com);
}
