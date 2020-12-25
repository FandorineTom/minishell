/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 23:44:22 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/15 21:18:20 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dst;
	unsigned int	index;

	if (!s)
		return (NULL);
	if (!(dst = (char *)malloc(sizeof(*s) * len + 1)))
		return (NULL);
	index = 0;
	if (ft_strlen(s) > start)
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
