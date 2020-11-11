/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 10:39:57 by snorthmo          #+#    #+#             */
/*   Updated: 2020/11/11 17:57:52 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		treat_flags(t_flags *flags, va_list args)
{
	int len;

	len = 0;
	if (flags->type == 'c')
		len += print_c(flags, args);
	else if (flags->type == 's')
		len += print_s(flags, args);
	else if (flags->type == 'u')
		len += print_u(flags, args);
	else if (flags->type == 'x')
		len += print_x(flags, args);
	else if (flags->type == 'X')
		len += print_x_big(flags, args);
	else if (flags->type == 'p')
		len += print_p(flags, args);
	else if (flags->type == 'd' || flags->type == 'i')
		len += print_d(flags, args);
	else if (flags->type == '%')
		len += print_perc(flags);
	return (len);
}

int		ft_printf(const char *line, ...)
{
	va_list	args;
	t_flags	flags;
	int		len;

	if (!line)
		return (-1);
	va_start(args, line);
	init_flags(&flags);
	len = 0;
	while (*line)
	{
		if (*line != '%')
			len += write(1, line, 1);
		else if (*line == '%')
		{
			parse_flags(&line, &flags, args);
			len += flags.wrong == 1 ? write(1, line, 1) :\
			treat_flags(&flags, args);
			init_flags(&flags);
		}
		if (*line)
			line++;
	}
	va_end(args);
	return (len);
}
