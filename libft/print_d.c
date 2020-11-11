/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_d.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 12:49:34 by snorthmo          #+#    #+#             */
/*   Updated: 2020/11/11 17:58:14 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_d_len(int num)
{
	int count;

	count = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		count++;
	while (num != 0)
	{
		count++;
		num /= 10;
	}
	return (count);
}

int		print_d_width_neg(t_flags *flags, int count, int num, int n)
{
	char	f;
	int		len;

	len = 0;
	f = !flags->zero && flags->flag == '0' ? '0' : ' ';
	if (flags->flag != '-' && f != '0')
	{
		while (n-- > count)
			len += write(1, &f, 1);
		len += write(1, "-", 1) + ft_putnbr(num);
	}
	else if (flags->flag != '-' && f == '0')
	{
		len += write(1, "-", 1);
		while (n-- > count)
			len += write(1, &f, 1);
		len += ft_putnbr(num);
	}
	else if (flags->flag == '-')
	{
		len += write(1, "-", 1) + ft_putnbr(num);
		while (n-- > count)
			len += write(1, &f, 1);
	}
	return (len);
}

int		print_d_precision_neg(t_flags *flags, int count, int num)
{
	int p;
	int tmp;
	int len;

	p = flags->precision;
	len = 0;
	tmp = p < count ? (flags->width - count) : (flags->width - p - 1);
	if (flags->flag != '-')
	{
		while (tmp-- > 0)
			len += write(1, " ", 1);
		len += write(1, "-", 1);
		while (p-- >= count)
			len += write(1, "0", 1);
		len += ft_putnbr(num);
		return (len);
	}
	len += write(1, "-", 1);
	while (p-- >= count)
		len += write(1, "0", 1);
	len += ft_putnbr(num);
	while (tmp-- > 0)
		len += write(1, " ", 1);
	return (len);
}

int		print_d(t_flags *flags, va_list args)
{
	int num;
	int count;
	int n;
	int len;

	num = va_arg(args, int);
	count = count_d_len(num);
	n = flags->width;
	len = 0;
	if (flags->zero && !num)
	{
		while (flags->width--)
			len += write(1, " ", 1);
		return (len);
	}
	if (!flags->precision)
		len += num >= 0 ? print_u_width(flags, count, num) :\
		print_d_width_neg(flags, count, num, n);
	else
		len += num >= 0 ? print_u_precision(flags, count, num) :\
		print_d_precision_neg(flags, count, num);
	return (len);
}
