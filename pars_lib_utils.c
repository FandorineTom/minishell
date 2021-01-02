/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_lib_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scopycat <scopycat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 20:17:21 by scopycat          #+#    #+#             */
/*   Updated: 2021/01/02 20:27:06 by scopycat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlen_space(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] && str[i] != ' ')
		i++;
	return (i);
}

size_t	ft_strlen_char(char *str, char c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (i);
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int		ft_strncmp(const char *str1, const char *str2, size_t len)
{
	size_t i;

	i = 0;
	if (len == 0)
		return (0);
	while (str1[i] && str1[i] == str2[i] && i < (len - 1))
		i++;
	return ((unsigned char)str1[i] - (unsigned char)str2[i]);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	size_t			i;
	unsigned int	size;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
		i++;
	if (start > i)
		return (ft_strdup(""));
	size = i - start;
	if (len > size)
		len = size;
	if (!(dest = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = 0;
	while (i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strchr(const char *str, int sym)
{
	int i;

	i = 0;
	if (str[i] == sym)
		return ((char*)str);
	while (str[i])
	{
		if (str[i] == sym)
		{
			str = str + i;
			return ((char*)str);
		}
		i++;
		if (str[i] == sym)
		{
			str = str + i;
			return ((char*)str);
		}
	}
	return (NULL);
}
