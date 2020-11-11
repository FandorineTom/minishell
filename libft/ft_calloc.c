/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 21:43:57 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/14 22:32:13 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	size_t	str_size;

	if ((size && FT_SIZE_MAX / size < count) || (count && FT_SIZE_MAX / count \
		< size))
		return (NULL);
	str_size = size * count;
	if (!(str = (void *)malloc(str_size)))
		return (NULL);
	str[str_size - 1] = '\0';
	while (str_size > 0)
	{
		str_size--;
		str[str_size] = '\0';
	}
	return ((void *)str);
}
