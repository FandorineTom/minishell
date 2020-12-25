/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 22:51:16 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/14 20:40:06 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_tmp;
	size_t			counter;

	s_tmp = (unsigned char *)s;
	counter = 0;
	while (n > 0)
	{
		if (*s_tmp == (unsigned char)c)
			return ((char *)s + counter);
		s_tmp++;
		n--;
		counter++;
	}
	return (0);
}
