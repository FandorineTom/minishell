/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 23:24:47 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/13 23:25:53 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int index;

	index = 0;
	while (index < n && (s1[index] || s2[index]))
	{
		if (s1[index] == s2[index])
			index++;
		else
			return ((unsigned char)(s1[index]) - (unsigned char)(s2[index]));
	}
	return (0);
}
