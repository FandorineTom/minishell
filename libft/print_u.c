/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_u.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:57:01 by snorthmo          #+#    #+#             */
/*   Updated: 2020/11/11 18:00:42 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		count_u_len(unsigned int num)
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

int		print_u_precision(t_flags *flags, int count, unsigned int num)
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
		len += ft_putnbr_unint(num);
	}
	else
	{
		while (p-- > count)
			len += write(1, "0", 1);
		len += ft_putnbr_unint(num);
		while (tmp-- > 0)
			len += write(1, " ", 1);
	}
	return (len);
}

int		print_u_width(t_flags *flags, int count, unsigned int num)
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
		len += ft_putnbr_unint(num);
	}
	else
	{
		len += ft_putnbr_unint(num);
		while (n-- > count)
			len += write(1, &f, 1);
	}
	return (len);
}

int		print_u(t_flags *flags, va_list args)
{
	unsigned int	num;
	int				count;
	int				len;

	num = va_arg(args, unsigned int);
	len = 0;
	count = count_u_len(num);
	if (flags->zero && !num)
	{
		while (flags->width--)
			len += write(1, " ", 1);
		return (len);
	}
	if (!flags->precision)
		len += print_u_width(flags, count, num);
	else
		len += print_u_precision(flags, count, num);
	return (len);
}
