/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 23:13:27 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/13 23:14:03 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		index;

	if (!s1 || !s2)
		return (NULL);
	result = (char *)malloc(sizeof(s1) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!result)
		return (NULL);
	index = 0;
	while (*s1)
		result[index++] = *(s1++);
	while (*s2)
		result[index++] = *(s2++);
	result[index] = '\0';
	return (result);
}
