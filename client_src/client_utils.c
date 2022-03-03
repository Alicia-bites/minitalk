/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:16:58 by amarchan          #+#    #+#             */
/*   Updated: 2022/03/02 14:35:20 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_minitalk.h"

int	ft_panic(int errcode)
{
	if (errcode == 1)
		ft_putstr("Usage : ./client <server P.I.D.> <message>", 1);
	else if (errcode == 2)
		ft_putstr("Missing PID or message.", 1);
	else if (errcode == SIGACT_FAIL)
		ft_putstr("Setting up sigaction failed.", 1);
	else if (errcode == INVALID_PID)
		ft_putstr("Invalid PID : PID must be a positive integer.", 1);
	else if (errcode == EMPTY_STR)
		ft_putstr("Empty string.", 1);
	else if (errcode == SIG_ERROR)
		ft_putstr("Signal error. Server down or wrong PID", 1);
	return (errcode);
}

//check if PID is valid
int pid_is_valid(char *s)
{
    while (*s)
	{
		if (!ft_isdigit(*s++))
			return (0);
	}
	return (1);
}

//Send each bit
int	ft_send_bit(int bit, int tries)
{
	int	signal;
	
	if (tries >= MAX_RETRIES)
		return (SIG_ERROR);
	if (bit == 1)
		signal = SIGUSR1;
	if (bit == 0)
		signal = SIGUSR2;
	if (kill(g_client.srv_pid, signal) == SIG_ERROR)
		return (ft_send_bit(bit, tries + 1));
	return (0);
}
