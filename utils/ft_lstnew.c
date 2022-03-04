/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 11:53:40 by amarchan          #+#    #+#             */
/*   Updated: 2022/03/04 09:47:10 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_minitalk.h"

t_lined_up	*ft_lstnew(int bit, pid_t pid)
{
	t_lined_up	*elt;

	elt = malloc(sizeof(t_lined_up));
	if (!elt)
	{
		ft_putstr("malloc failed", 1);
		ft_lstclear_back(&g_pile);
		exit(EXIT_FAILURE);
	}
	elt->bit = bit;
	elt->pid = pid;
	elt->prev = NULL;
	elt->next = NULL;
	return (elt);
}
