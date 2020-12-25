/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 22:55:14 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/13 22:56:02 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *tmp;

	if (!src && !dst)
		return (0);
	tmp = (char *)dst;
	while (n > 0)
	{
		*tmp = *(char *)src;
		tmp++;
		src++;
		n--;
	}
	return (dst);
}
