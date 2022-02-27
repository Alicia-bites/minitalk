/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:16:58 by amarchan          #+#    #+#             */
/*   Updated: 2022/02/27 18:20:54 by amarchan         ###   ########.fr       */
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
		ft_putstr("Invalid P.I.D. P.I.D. must be digits only.", 1);
	else if (errcode == EMPTY_STR)
		ft_putstr("Empty string.", 1);
	else if (errcode == SRV_TIMEOUT)
		ft_putstr("Impossible to reach server", 1);
	else if (errcode == SIG_ERROR)
		ft_putstr("Signal error. Server might be down.", 1);
	return (errcode);
}

//termine le message du client par un '\0' soit 8 bits à 0
int	ft_msg_ender(void)
{
	int	i;

	i = 0;
	while (i++ < 8)
	{
		if (ft_send_bit(0, 0) == -1)
			return (-1);
		while (g_client.flags != PONG_OK)
			pause();
	}
	return (0);
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
		ft_send_bit(bit, tries + 1);
	return (0);
}
