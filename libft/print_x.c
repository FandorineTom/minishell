/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 19:12:20 by snorthmo          #+#    #+#             */
/*   Updated: 2020/11/11 18:01:00 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_x_len(unsigned int num)
{
	int count;

	count = 0;
	while (num >= 16)
	{
		num = num / 16;
		count++;
	}
	count++;
	return (count);
}

int		print_x_precision(t_flags *flags, int count, unsigned int num)
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
		len += print_hexa(num);
	}
	else
	{
		while (p-- > count)
			len += write(1, "0", 1);
		len += print_hexa(num);
		while (tmp-- > 0)
			len += write(1, " ", 1);
	}
	return (len);
}

int		print_x_width(t_flags *flags, int count, unsigned int num)
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
		len += print_hexa(num);
	}
	else
	{
		len += print_hexa(num);
		while (n-- > count)
			len += write(1, &f, 1);
	}
	return (len);
}

int		print_x(t_flags *flags, va_list args)
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
		len += print_x_width(flags, count, num);
	else
		len += print_x_precision(flags, count, num);
	return (len);
}
