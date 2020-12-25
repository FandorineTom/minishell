/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 23:18:17 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/13 23:19:11 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	unsigned int index;

	index = 0;
	if (dstsize)
	{
		while (src[index] && (dstsize - 1) != 0)
		{
			dst[index] = src[index];
			dstsize--;
			index++;
		}
		dst[index] = '\0';
	}
	while (src[index])
		index++;
	return (index);
}
