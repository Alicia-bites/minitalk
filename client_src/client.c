/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:17:22 by amarchan          #+#    #+#             */
/*   Updated: 2022/03/04 09:28:11 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_minitalk.h"

t_client	g_client;

//Break char down to bits,
//Wait until client flag indicates precedent bit has been received,
//if 8 bits have been sent, put g_client.bits_sent to CHAR_SENT -->
//allow ft_send_msg to go to the next char
static int	ft_send_char(char c)
{
	static int	i = 7;
	int			res;

	res = 0;
	while (i >= 0 && g_client.flags == PONG_OK)
	{
		res = (c >> i) & 1;
		g_client.flags = 0;
		if (ft_send_bit(res, 0) == SIG_ERROR)
		{
			ft_panic(SIG_ERROR);
			exit(EXIT_FAILURE);
		}
		if (i == 0)
		{
			g_client.bits_sent = CHAR_SENT;
			i = 7;
			return (0);
		}
		while (g_client.flags != PONG_OK)
			pause();
		usleep(10);
		i--;
	}
	return (0);
}

//Get client msg string and send it char by char to ft_send_char.
//Only moves on to next char if every bits of precedent 
//char have been sent (CHAR_SENT) ->
//and if last bit sent has been received by the server (PONG_OK).
static int	ft_send_msg(char *msg)
{
	int	i;

	i = 0;
	msg = ft_strcat(g_client.msg, "\n");
	while (msg[i] && g_client.flags == PONG_OK)
	{
		if (g_client.bits_sent == CHAR_SENT)
			i++;
		if (ft_send_char(msg[i]) == SIG_ERROR)
			return (SIG_ERROR);
		while (g_client.flags != PONG_OK)
			pause();
	}
	return (0);
}

//When SIGUSR1 is received ->
//use client flag to indicate server has confirmed bit reception
//When SIGUSR2 is received -> 
//use client flag to indicate server has received the entire message
void	handler(int signum, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (signum == SIGUSR1)
		g_client.flags = PONG_OK;
	if (signum == SIGUSR2)
	{
		ft_putstr("Your message has been received by the server!", 1);
		exit(EXIT_SUCCESS);
	}
}

//Set up signal catcher function
static int	ft_set_sigaction(void)
{
	struct sigaction	action;

	action.sa_sigaction = handler;
	action.sa_flags = SA_SIGINFO;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGUSR1);
	sigaddset(&action.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &action, 0) == -1)
		return (-1);
	if (sigaction(SIGUSR2, &action, 0) == -1)
		return (-1);
	return (0);
}

//client --> usage : ./client <PID du server> <message>
int	main(int argc, char **argv)
{
	int	msg_error;

	usleep(10);
	if (ft_set_sigaction() == -1)
		return (ft_panic(ACTION_FAIL));
	if (argc < 3)
		return (ft_panic(argc));
	g_client.msg = argv[2];
	g_client.msg_len = ft_strlen(argv[2]);
	g_client.srv_pid = ft_atoi(argv[1]);
	g_client.flags = PONG_OK;
	g_client.bits_sent = 0;
	if (g_client.srv_pid <= 0 || pid_is_valid(argv[1]) == 0)
		return (ft_panic(INVALID_PID));
	if (g_client.msg_len == 0)
		return (ft_panic(EMPTY_STR));
	msg_error = ft_send_msg(g_client.msg);
	if (msg_error != 0)
		return (ft_panic(SIG_ERROR));
	while (1)
		pause();
}
