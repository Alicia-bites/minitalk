/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:37:28 by amarchan          #+#    #+#             */
/*   Updated: 2022/02/03 13:55:53 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minitalk.h"

void	ft_putstr(char *s, int isend)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i])
	{
		if (isend == 0)
			ft_putchar(s[i++]);
		if (isend == 1)
			ft_putchar("\n");
}
