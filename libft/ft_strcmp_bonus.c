/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 23:09:23 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/13 23:09:56 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned int		index;
	const unsigned char	*s1_tmp;
	const unsigned char	*s2_tmp;

	s1_tmp = (const unsigned char *)s1;
	s2_tmp = (const unsigned char *)s2;
	index = 0;
	while (s1_tmp[index] || s2_tmp[index])
	{
		if (s1_tmp[index] != s2_tmp[index])
			return (s1_tmp[index] - s2_tmp[index]);
		index++;
	}
	return (0);
}
