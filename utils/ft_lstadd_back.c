/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:53:03 by amarchan          #+#    #+#             */
/*   Updated: 2022/02/16 19:00:34 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_minitalk.h"
void	ft_lstadd_back(t_lined_up **first_elt, t_lined_up *new)
{
	t_lined_up	*iterator;

	iterator = *first_elt;
	if (first_elt && new)
	{
		if (!*first_elt)
			*first_elt = new;
		else
		{	
			while (iterator->next)
				iterator = iterator->next;
			iterator->next = new;
		}
	}
}
