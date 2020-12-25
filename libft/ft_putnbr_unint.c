/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_unint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 17:10:40 by snorthmo          #+#    #+#             */
/*   Updated: 2020/11/11 18:05:36 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putnbr_unint(unsigned int n)
{
	int len;

	len = 0;
	if (n < 10)
	{
		len += ft_putchar((n + 48));
		return (len);
	}
	len += ft_putnbr((n / 10));
	len += ft_putchar(((n % 10) + 48));
	return (len);
}
