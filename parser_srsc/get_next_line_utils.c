/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 15:33:12 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/23 15:40:04 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *str)
{
	char	*dest;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	dest = (char*)malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!dest)
		return (NULL);
	while (str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr_gnl(char *str)
{
	unsigned char	s;

	s = '\n';
	if (!str)
		return (NULL);
	while (*str)
	{
		if (*str == s)
		{
			*str = '\0';
			return (str);
		}
		str++;
	}
	return (NULL);
}

char	*ft_strjoin_gnl(char **l1, char *l2)
{
	char	*buf;
	int		i;
	char	*tmp;

	if (!(*l1) && !l2)
		return (NULL);
	buf = (char*)malloc((ft_strlen(*l1) + ft_strlen(l2) + 1) * sizeof(char));
	if (!buf)
		return (NULL);
	i = 0;
	while (l1 && *l1 && **l1)
		buf[i++] = *(*l1)++;
	*l1 = *l1 - i;
	if (*l1)
		free(*l1);
	*l1 = NULL;
	tmp = l2;
	while (l2 && *l2)
		buf[i++] = *l2++;
	buf[i] = '\0';
	l2 = tmp;
	return (buf);
}
