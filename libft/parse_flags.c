/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_flags.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/13 12:48:36 by snorthmo          #+#    #+#             */
/*   Updated: 2020/11/11 17:57:58 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	check_flag(const char **line, t_flags *flags)
{
	while (**line == '-')
	{
		flags->flag = '-';
		*line = *line + 1;
	}
	if (**line == '0' && !flags->flag)
	{
		while (**line == '0')
		{
			flags->flag = '0';
			*line = *line + 1;
		}
	}
	if (**line == '+')
		flags->flag = '+';
	else if (**line == ' ')
		flags->flag = ' ';
	else if (**line == '#')
		flags->flag = '#';
	else
		return ;
	*line = *line + 1;
}

void	check_width(const char **line, t_flags *flags, va_list args)
{
	long n;

	while (**line == '-' || **line == '0')
	{
		flags->flag = '-';
		*line = *line + 1;
	}
	while (ft_isdigit((int)**line))
	{
		flags->width = flags->width * 10 + **line - 48;
		*line = *line + 1;
	}
	if (**line == '*')
	{
		n = (long)va_arg(args, int);
		if (n >= 0)
			flags->width = n;
		else
		{
			flags->flag = '-';
			flags->width = -n;
		}
		*line = *line + 1;
	}
}

void	check_type(const char **line, t_flags *flags)
{
	if (**line == 'c')
		flags->type = 'c';
	else if (**line == 's')
		flags->type = 's';
	else if (**line == 'p')
		flags->type = 'p';
	else if (**line == 'd' || **line == 'i')
		flags->type = 'd';
	else if (**line == 'u')
		flags->type = 'u';
	else if (**line == 'x')
		flags->type = 'x';
	else if (**line == 'X')
		flags->type = 'X';
	else if (**line == '%')
		flags->type = '%';
	else if (**line == '\0')
		flags->wrong = 2;
	else
		flags->wrong = 1;
}

void	check_precision(const char **line, t_flags *flags, va_list args)
{
	int n;

	if (**line == '.')
	{
		*line = *line + 1;
		if ((**line == '0' || !ft_isdigit((int)**line)) && **line != '*')
			flags->zero = 1;
	}
	while (ft_isdigit((int)**line))
	{
		flags->precision = flags->precision * 10 + **line - 48;
		*line = *line + 1;
		if (flags->precision > 0)
			flags->zero = 0;
	}
	if (**line == '*')
	{
		n = va_arg(args, int);
		if (n > 0)
			flags->precision = n;
		if (n == 0)
			flags->zero = 1;
		*line = *line + 1;
	}
}

int		parse_flags(const char **line, t_flags *flags, va_list args)
{
	*line = *line + 1;
	check_flag(line, flags);
	check_width(line, flags, args);
	check_precision(line, flags, args);
	check_type(line, flags);
	return (0);
}
