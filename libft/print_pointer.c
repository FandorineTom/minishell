/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 21:45:08 by snorthmo          #+#    #+#             */
/*   Updated: 2020/11/11 17:59:00 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		print_pointer(int *n)
{
	int len;

	len = 0;
	len += write(1, "0x", 2);
	len += print_hexa((unsigned long)n);
	return (len);
}
