/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snorthmo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/13 22:28:39 by snorthmo          #+#    #+#             */
/*   Updated: 2020/05/13 22:28:41 by snorthmo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *tempo;

	if (alst && *alst)
	{
		tempo = *alst;
		while (tempo->next != 0)
			tempo = tempo->next;
		tempo->next = new;
	}
	else if (alst && !*alst)
		*alst = new;
}
