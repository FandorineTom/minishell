/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 20:51:53 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/14 12:45:12 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	unsigned int index;
	unsigned int i;

	if ((ft_strlen(to_find) == 0))
		return ((char *)str);
	i = 0;
	while (str[i] && i < len)
	{
		index = 0;
		if (str[i] == to_find[index])
		{
			while (to_find[index] && to_find[index] == str[i + index] && \
				(i + index) < len)
				index++;
			if (to_find[index] == '\0')
				return ((char *)&str[i]);
		}
		i++;
	}
	return (NULL);
}
