/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 11:53:40 by amarchan          #+#    #+#             */
/*   Updated: 2022/03/01 16:30:31 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_minitalk.h"

t_lined_up	*ft_lstnew(int bit, pid_t pid)
{
	t_lined_up	*elt;

	elt = malloc(sizeof(t_lined_up));
	if (!elt)
		return (NULL);
	elt->bit = bit;
	elt->pid = pid;
	elt->prev = NULL;
	elt->next = NULL;
	return (elt);
}
