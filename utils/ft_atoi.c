/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:02:59 by amarchan          #+#    #+#             */
/*   Updated: 2022/02/03 13:54:40 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_minitalk.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	res;
	int	negative;

	i = 0;
	res = 0;
	negative = 1;
	while (str[i] && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
			|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			negative *= -1;
		i++;
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * negative);
}
