/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 22:45:48 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/13 22:50:36 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char		*dst_tmp;
	const unsigned char	*src_tmp;
	size_t				counter;

	dst_tmp = (unsigned char *)dst;
	src_tmp = (const unsigned char *)src;
	counter = 0;
	while (n > 0)
	{
		if (*src_tmp == (unsigned char)c)
		{
			*dst_tmp = *src_tmp;
			return ((char *)dst + counter + 1);
		}
		*dst_tmp = *src_tmp;
		dst_tmp++;
		src_tmp++;
		n--;
		counter++;
	}
	return (0);
}
