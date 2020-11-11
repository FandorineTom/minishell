/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrimwhole_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 23:41:42 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/13 23:43:52 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrimwhole(char const *s1, char const *set)
{
	char			*result;
	unsigned int	index;
	unsigned int	i;
	unsigned int	check;

	if (!s1 || !set || !(result = (char *)malloc(sizeof(*s1) * \
		(ft_strlen(s1) - ft_strlen(set)) + 1)))
		return (NULL);
	index = 0;
	i = 0;
	while (*s1)
	{
		check = 1;
		i = 0;
		while (set[i])
		{
			if (*s1 == set[i++])
				check = 0;
		}
		if (check == 1)
			result[index++] = *s1;
		s1++;
	}
	return (result);
}
