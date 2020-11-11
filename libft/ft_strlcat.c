/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 23:14:56 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/14 23:26:52 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t index;

	index = 0;
	while (dst[index])
		index++;
	if (dstsize > index)
	{
		dstsize -= index;
		while (*src && dstsize > 1)
		{
			dst[index] = *src;
			dstsize--;
			index++;
			src++;
		}
		dst[index] = '\0';
	}
	else
		return (dstsize + (ft_strlen(src)));
	while (*src)
	{
		src++;
		index++;
	}
	return (index);
}
