/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:37:28 by amarchan          #+#    #+#             */
/*   Updated: 2022/02/08 14:33:30 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minitalk.h"

void	ft_putstr(char *s, int isend)
{
	if (!s)
		return ;
	while (*s)
		ft_putchar(*s++);
	if (isend >= 1)
		ft_putchar('\n');
}