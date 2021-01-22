/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 11:46:35 by snorthmo          #+#    #+#             */
/*   Updated: 2021/01/22 13:46:15 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long long	result;
	long long	result_tempo;
	int			negative;

	result = 0;
	negative = 1;
	while (*str && (*str == '\t' || *str == '\r' || *str == ' '\
			|| *str == '\f' || *str == '\v' || *str == '\n'))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative = -1;
		str++;
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		result_tempo = result;
		result = result * 10 + (*str - '0');
		str++;
		if (result_tempo > result)
			return (negative == 1 ? 0 : 0);
	}
	return (result * negative);
}
