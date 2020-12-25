/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/23 14:55:30 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/13 22:27:57 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long	ft_int_lenght(int n)
{
	int		len;

	len = 0;
	if (n < 0)
		len++;
	while (n / 10 >= 1 || n / 10 < 0)
	{
		len++;
		n /= 10;
	}
	len++;
	return (len);
}

char		*ft_itoa(int n)
{
	long	int_len;
	char	*result;
	size_t	i;
	long	n_long;

	int_len = ft_int_lenght(n);
	if (!(result = (char *)ft_calloc((int_len + 1), sizeof(char))))
		return (NULL);
	i = int_len - 1;
	n_long = (long)n;
	if (n < 0)
	{
		result[0] = '-';
		n_long = -n_long;
	}
	while (n_long / 10 > 0)
	{
		result[i] = (char)(n_long % 10 + 48);
		i--;
		n_long /= 10;
	}
	result[i] = (char)(n_long + 48);
	return (result);
}
