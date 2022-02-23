/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 19:19:20 by amarchan          #+#    #+#             */
/*   Updated: 2022/02/23 14:26:33 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_minitalk.h"

void	ft_lstclear(t_lined_up **lst)
{
	t_lined_up	*iterator;
	t_lined_up	*prev;

	iterator = *lst;
	prev = NULL;
	while (iterator)
	{
		prev = iterator;
		iterator = iterator->next;
		free(prev);
	}
	*lst = NULL;
}