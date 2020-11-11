/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_perc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:15:54 by snorthmo          #+#    #+#             */
/*   Updated: 2020/11/11 17:58:51 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		print_perc(t_flags *flags)
{
	char	f;
	int		len;

	len = 0;
	f = flags->flag == '0' ? '0' : ' ';
	if (flags->flag != '-')
	{
		while (flags->width > 1)
		{
			len += write(1, &f, 1);
			flags->width--;
		}
		len += ft_putchar('%');
	}
	else
	{
		len += ft_putchar('%');
		while (flags->width > 1)
		{
			len += write(1, &f, 1);
			flags->width--;
		}
	}
	return (len);
}
