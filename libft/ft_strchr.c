/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 23:08:08 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/18 17:45:21 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned int	index;
	char			*tempo;

	index = 0;
	tempo = (char *)s;
	while (tempo[index])
	{
		if (tempo[index] == (char)c)
			return (&tempo[index]);
		index++;
	}
	if (tempo[index] == (char)c)
		return (&tempo[index]);
	return (0);
}
