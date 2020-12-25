/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 17:10:40 by snorthmo          #+#    #+#             */
/*   Updated: 2020/11/11 18:08:19 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr(int n)
{
	int len;

	len = 0;
	if (n == -2147483648)
	{
		len += ft_putstr("2147483648");
		return (len);
	}
	if (n < 0)
		n = -n;
	if (n < 10)
	{
		len += ft_putchar((n + 48));
		return (len);
	}
	len += ft_putnbr((n / 10));
	len += ft_putchar(((n % 10) + 48));
	return (len);
}
