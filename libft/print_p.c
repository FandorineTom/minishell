/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 09:57:16 by snorthmo          #+#    #+#             */
/*   Updated: 2020/11/11 17:58:40 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_p_len(unsigned long n)
{
	int len;

	len = 0;
	if (n >= 16)
		len += count_p_len(n / 16);
	n = n % 16;
	n += n < 10 ? '0' : 'a' - 10;
	len++;
	return (len);
}

int		print_p_precision(t_flags *flags, int c, int *p)
{
	int len;
	int tmp;

	len = 0;
	tmp = flags->precision < c ? (flags->width - c) :\
	(flags->width - flags->precision);
	if (flags->flag != '-')
	{
		while (tmp-- > 0)
			len += write(1, " ", 1);
		len += write(1, "0x", 2);
		while (flags->precision-- > (c - 2))
			len += write(1, "0", 1);
		len += print_hexa((unsigned long)p);
	}
	else
	{
		len += write(1, "0x", 2);
		while (flags->precision-- > (c - 2))
			len += write(1, "0", 1);
		len += print_hexa((unsigned long)p);
		while (tmp-- > 0)
			len += write(1, " ", 1);
	}
	return (len);
}

int		print_p_null(t_flags *flags, int w)
{
	int p;
	int len;

	p = flags->zero ? 0 : 1;
	len = 0;
	if (flags->precision != 0)
		p = flags->precision;
	if (flags->flag != '-')
	{
		while (w-- > (p + 2))
			len += write(1, " ", 1);
		len += write(1, "0x", 2);
		while (p-- > 0)
			len += write(1, "0", 1);
	}
	else
	{
		len += write(1, "0x", 2);
		w -= (2 + p);
		while (p-- > 0)
			len += write(1, "0", 1);
		while (w-- > 0)
			len += write(1, " ", 1);
	}
	return (len);
}

int		print_p(t_flags *flags, va_list args)
{
	int *p;
	int count;
	int	len;

	len = 0;
	p = va_arg(args, int*);
	count = count_p_len((unsigned long)p) + 2;
	if (!p)
		len += print_p_null(flags, flags->width);
	else if (flags->precision > (count - 2))
		len += print_p_precision(flags, count, p);
	else if (flags->flag != '-')
	{
		while (flags->width-- > count)
			len += write(1, " ", 1);
		len += print_pointer(p);
	}
	else
	{
		len += print_pointer(p);
		while (flags->width-- > count)
			len += write(1, " ", 1);
	}
	return (len);
}
