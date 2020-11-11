/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <snorthmo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 11:48:52 by snorthmo          #+#    #+#             */
/*   Updated: 2020/11/11 17:57:41 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	init_flags(t_flags *flags)
{
	flags->flag = 0;
	flags->precision = 0;
	flags->type = 0;
	flags->width = 0;
	flags->zero = 0;
	flags->wrong = 0;
}
