/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 23:31:58 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/13 23:33:13 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *to_find)
{
	int index;

	if (ft_strlen(to_find) == 0)
		return ((char *)str);
	while (*str)
	{
		index = 0;
		if (*str == to_find[index])
		{
			while (to_find[index] && to_find[index] == *(str + index))
				index++;
			if (to_find[index] == '\0')
				return ((char *)str);
		}
		str++;
	}
	return (0);
}
