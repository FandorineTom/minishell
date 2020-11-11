/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 22:44:50 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/13 22:45:16 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int		count;

	count = 1;
	if (!lst)
		return (0);
	while (lst->next != 0)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}
