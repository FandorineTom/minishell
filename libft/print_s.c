/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_s.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/17 15:00:17 by snorthmo          #+#    #+#             */
/*   Updated: 2020/11/11 17:59:09 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		print_s_precision(t_flags *flags, char *str, size_t w, size_t p)
{
	size_t	min;
	int		len;

	len = 0;
	min = p < ft_strlen(str) ? p : ft_strlen(str);
	if (flags->flag != '-')
	{
		while (w-- > min)
			len += write(1, " ", 1);
		while (p-- && *str != '\0')
		{
			len += write(1, str, 1);
			str++;
		}
		return (len);
	}
	while (p-- && *str != '\0')
	{
		len += write(1, str, 1);
		str++;
	}
	while (w-- > min)
		len += write(1, " ", 1);
	return (len);
}

int		print_s_width(t_flags *flags, char *str)
{
	size_t	n;
	int		len;
	char	f;

	n = flags->width;
	len = 0;
	f = flags->flag == '0' ? '0' : ' ';
	if (flags->flag != '-')
	{
		while (n-- > ft_strlen(str))
			len += write(1, &f, 1);
		len += ft_putstr(str);
	}
	else
	{
		len += ft_putstr(str);
		while (n-- > ft_strlen(str))
			len += write(1, &f, 1);
	}
	return (len);
}

int		print_s_null(t_flags *flags, int w, int min)
{
	char	*str;
	int		tmp;
	int		len;

	str = "(null)";
	len = 0;
	if (flags->zero)
		while (w--)
			len += write(1, " ", 1);
	else if (flags->flag != '-')
	{
		while (w-- > min)
			len += write(1, " ", 1);
		while (min-- > 0 && *str)
			len += write(1, str++, 1);
	}
	else
	{
		tmp = min;
		while (min-- > 0 && *str)
			len += write(1, str++, 1);
		while (w-- > tmp)
			len += write(1, " ", 1);
	}
	return (len);
}

int		print_s(t_flags *flags, va_list args)
{
	int		w;
	int		p;
	char	*str;
	int		min;
	int		len;

	w = flags->width;
	p = flags->precision;
	len = 0;
	if ((str = va_arg(args, char*)) == NULL)
	{
		p = flags->precision ? flags->precision : 6;
		min = p > 6 ? 6 : p;
		len += print_s_null(flags, w, min);
	}
	else if (flags->zero)
		while (w--)
			len += write(1, " ", 1);
	else if (p)
		len += print_s_precision(flags, str, (size_t)w, (size_t)p);
	else
		len += print_s_width(flags, str);
	return (len);
}
