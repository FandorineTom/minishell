/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 23:30:24 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/13 23:31:30 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		index;
	char	*tempo;

	index = 0;
	tempo = (char *)s;
	while (tempo[index])
		index++;
	while (index >= 0)
	{
		if (tempo[index] == (char)c)
			return (&tempo[index]);
		index--;
	}
	return (0);
}
