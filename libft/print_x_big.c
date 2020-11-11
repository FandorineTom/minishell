/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x_big.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 11:52:45 by snorthmo          #+#    #+#             */
/*   Updated: 2020/11/11 18:00:50 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		print_x_precision_big(t_flags *flags, int count, unsigned int num)
{
	int p;
	int tmp;
	int len;

	p = flags->precision;
	len = 0;
	tmp = p < count ? (flags->width - count) : (flags->width - p);
	if (flags->flag != '-')
	{
		while (tmp-- > 0)
			len += write(1, " ", 1);
		while (p-- > count)
			len += write(1, "0", 1);
		len += print_hexa_big(num);
	}
	else
	{
		while (p-- > count)
			len += write(1, "0", 1);
		len += print_hexa_big(num);
		while (tmp-- > 0)
			len += write(1, " ", 1);
	}
	return (len);
}

int		print_x_width_big(t_flags *flags, int count, unsigned int num)
{
	int		n;
	char	f;
	int		len;

	n = flags->width;
	len = 0;
	f = flags->flag == '0' ? '0' : ' ';
	if (flags->zero)
		f = ' ';
	if (flags->flag != '-')
	{
		while (n-- > count)
			len += write(1, &f, 1);
		len += print_hexa_big(num);
	}
	else
	{
		len += print_hexa_big(num);
		while (n-- > count)
			len += write(1, &f, 1);
	}
	return (len);
}

int		print_x_big(t_flags *flags, va_list args)
{
	unsigned int	num;
	int				count;
	int				len;

	num = va_arg(args, unsigned int);
	count = count_x_len(num);
	len = 0;
	if (flags->zero && !num)
	{
		while (flags->width--)
			len += write(1, " ", 1);
		return (len);
	}
	if (!flags->precision)
		len += print_x_width_big(flags, count, num);
	else
		len += print_x_precision_big(flags, count, num);
	return (len);
}
