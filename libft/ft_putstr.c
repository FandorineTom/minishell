/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 17:07:49 by snorthmo          #+#    #+#             */
/*   Updated: 2020/11/11 18:08:03 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putstr(char *s)
{
	int len;

	len = 0;
	if (s)
	{
		while (*s)
		{
			len += ft_putchar(*s);
			s++;
		}
	}
	return (len);
}
