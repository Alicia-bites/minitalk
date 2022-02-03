/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 17:53:03 by amarchan          #+#    #+#             */
/*   Updated: 2022/02/03 13:43:50 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minitalk.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*iterator;

	iterator = *alst;
	if (alst && new)
	{
		if (!*alst)
			*alst = new;
		else
		{	
			while (iterator->next)
				iterator = iterator->next;
			iterator->next = new;
		}
	}
}
