/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 13:41:13 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/17 17:02:31 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		append_line(char **line, char **leftovers)
{
	int		len;
	char	*tmp;

	len = 0;
	while (leftovers[0][len] != '\n' && leftovers[0][len] != '\0')
		len++;
	if (leftovers[0][len] == '\n')
	{
		if (!(*line = ft_substr(*leftovers, 0, len)))
			return (-1);
		if (!(tmp = ft_strjoin("", *leftovers + len + 1)))
			return (-1);
		free(*leftovers);
		*leftovers = tmp;
	}
	else if (leftovers[0][len] == '\0')
	{
		if (!(*line = ft_strjoin("", *leftovers)))
			return (-1);
		free(*leftovers);
		*leftovers = NULL;
		return (0);
	}
	return (1);
}

int		to_return(char **line, char **leftovers, int ret)
{
	if (ret < 0)
		return (-1);
	else if (!ret && !*leftovers && *line)
		return (0);
	else if (!ret && !*leftovers && !*line)
	{
		if (!(*line = ft_strjoin("", "")))
			return (-1);
		return (0);
	}
	else
		return (append_line(line, leftovers));
}

int		actually_gnl(int fd, char **line, char **leftovers)
{
	char			*buf;
	int				ret;
	char			*tmp;

	if (!(buf = (char *)malloc(BUFFER_SIZE + 1)))
		return (-1);
	while ((ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		if (*leftovers == NULL)
		{
			if (!(*leftovers = ft_strjoin("", buf)))
				return (freemem(NULL, fd, -1, &buf));
		}
		else
		{
			tmp = *leftovers;
			if (!(*leftovers = ft_strjoin(*leftovers, buf)))
				return (freemem(NULL, fd, -1, &buf));
			free(tmp);
		}
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (freemem(NULL, fd, 0, &buf) + to_return(line, leftovers, ret));
}

t_struct	*new_list(int fd)
{
	t_struct *new;

	if (!(new = (t_struct *)malloc(sizeof(t_struct))))
		return (0);
	new->fd = fd;
	new->leftovers = NULL;
	new->next = NULL;
	return (new);
}

int		get_next_line(int fd, char **line)
{
	static t_struct	*fd_list;
	t_struct		*tmp;
	int				res;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	*line = NULL;
	if (!fd_list)
		if (!(fd_list = new_list(fd)))
			return (-1);
	tmp = fd_list;
	while (tmp->fd != fd)
	{
		if (tmp->next == NULL)
		{
			if (!(tmp->next = new_list(fd)))
				return (freemem(&fd_list, fd, -1, NULL));
		}
		tmp = tmp->next;
	}
	res = actually_gnl(fd, line, &tmp->leftovers);
	return (res == 1 ? res : freemem(&fd_list, fd, res, NULL));
}
