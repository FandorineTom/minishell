/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_c.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 12:41:08 by snorthmo          #+#    #+#             */
/*   Updated: 2020/11/11 17:58:07 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		print_c(t_flags *flags, va_list args)
{
	int n;
	int len;

	n = flags->width;
	len = 0;
	if (flags->flag != '-')
	{
		while (n > 1)
		{
			len += write(1, " ", 1);
			n--;
		}
		len += ft_putchar(va_arg(args, int));
	}
	else
	{
		len += ft_putchar(va_arg(args, int));
		while (n > 1)
		{
			len += write(1, " ", 1);
			n--;
		}
	}
	return (len);
}
