/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 13:41:29 by snorthmo          #+#    #+#             */
/*   Updated: 2020/10/25 14:04:43 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

int		freemem(t_struct **list, int fd, int res, char **str)
{
	t_struct *tmp;

	if (str)
	{
		if (*str)
		{
			free(*str);
			*str = NULL;
		}
	}
	else if (res == -1)
	{
		if (list)
		{
			while (*list)
			{
				tmp = (*list)->next;
				free(*list);
				*list = tmp;
			}
		}
	}
	else
		return (delnode(list, fd));
	return (res == 0 ? 0 : -1);
}

int		delnode(t_struct **list, int fd)
{
	t_struct *tmp;
	t_struct *tmp_del;

	tmp = *list;
	tmp_del = *list;
	while (tmp_del->fd != fd)
	{
		tmp = tmp_del;
		tmp_del = tmp_del->next;
	}
	if (tmp->next != tmp_del->next)
		tmp->next = tmp_del->next;
	else
		*list = (*list)->next;
	free(tmp_del);
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dst;
	unsigned int	index;
	unsigned int	len_s;

	if (!s)
		return (NULL);
	if (!(dst = (char *)malloc(sizeof(*s) * len + 1)))
		return (NULL);
	index = 0;
	len_s = 0;
	while (s[len_s])
		len_s++;
	if (len_s > start)
	{
		while (index < len)
		{
			dst[index] = s[start + index];
			index++;
		}
	}
	dst[index] = '\0';
	return (dst);
}
