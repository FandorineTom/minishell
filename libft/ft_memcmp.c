/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 22:53:04 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/13 22:54:14 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s1_tmp;
	unsigned char	*s2_tmp;
	int				res;

	s1_tmp = (unsigned char *)s1;
	s2_tmp = (unsigned char *)s2;
	while (n > 0)
	{
		if (*s1_tmp == *s2_tmp)
		{
			s1_tmp++;
			s2_tmp++;
			n--;
		}
		else
		{
			res = *s1_tmp - *s2_tmp;
			return (res);
		}
	}
	return (0);
}
