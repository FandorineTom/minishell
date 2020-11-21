/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hexa.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 17:07:00 by snorthmo          #+#    #+#             */
/*   Updated: 2020/11/11 17:58:33 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	print_hexa(unsigned long n)
{
	int len;

	len = 0;
	if (n >= 16)
		len += print_hexa(n / 16);
	n = n % 16;
	n += n < 10 ? '0' : 'a' - 10;
	len += write(1, &n, 1);
	return (len);
}