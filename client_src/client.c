/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:17:22 by amarchan          #+#    #+#             */
/*   Updated: 2022/02/24 14:17:25 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_minitalk.h"

t_client	g_client;

//Send each bit
int    ft_send_bit(int bit, int tries)
{
    int signal;

    if (tries >= MAX_RETRIES)
        return (SIG_ERROR);
    if (bit == 1)
        signal = SIGUSR1;
    if (bit == 0)
        signal = SIGUSR2;
    //printf("bit : %d", bit);
    if (kill(g_client.srv_pid, signal) == SIG_ERROR)
        ft_send_bit(bit, tries + 1);
}

//Break char down to bits,
//Wait until client flag indicates precedent bit has been received,
//if 8 bits have been sent, put g_client.bits_sent to CHAR_SENT -->
//allow ft_send_msg to go to the next char
static int ft_send_char(char c)
{
    int res = 0;
    static int i = 7;
    while (i >= 0 && g_client.flags == PONG_OK)
    {
        res = (c >> i) & 1;
        g_client.flags = 0;
        if (ft_send_bit(res, 0) == SIG_ERROR)
            return (SIG_ERROR);
        if (i == 0)
        { 
            g_client.bits_sent = CHAR_SENT;
            i = 7;
            return (0);
        }
        puts("before 1");
        while (g_client.flags != PONG_OK)
            pause();
        //printf("i : %d\n", i);
        puts("after 1");
        i--;
    }
    return (0);
}

//Get client msg string and send it char by char to ft_send_char.
//Only moves on to next char if every bits of precedent char have been sent (CHAR_SENT) ->
//and if last bit sent has been received by the server (PONG_OK).
static int    ft_send_msg(char *msg)
{
    int i;

    i = 0;
    while (msg[i] && g_client.flags == PONG_OK)
    {
        
        if (g_client.bits_sent == CHAR_SENT)
            i++;
        if (ft_send_char(msg[i]) == SIG_ERROR)
            return (SIG_ERROR);
        puts("before 2");
        while (g_client.flags != PONG_OK)
            pause();
        puts("before 2");
    }
    if (*msg = '\0' && g_client.flags == PONG_OK)
        if (ft_msg_ender() == SIG_ERROR)
            return (SIG_ERROR);
    return (0);
}

//When SIGUSR1 is received -> use client flag to indicate server has confirmed bit reception
//When SIGUSR2 is received -> use client flag to indicate server has received the entire message
static void	handler(int signum)
{
	if (signum == SIGUSR1)
        g_client.flags = PONG_OK;
        
    if (signum == SIGUSR2)
        g_client.flags = MSG_R;
}

//set up sigaction. When signal SIGUSR1 received --> send next bit
static int ft_set_sigaction (void)
{
    struct sigaction action;

    sigemptyset(&action.sa_mask);
    action.sa_sigaction = NULL;
    action.sa_handler = &handler;
    if (sigaction(SIGUSR1, &action, 0) == -1)
        return (-1);
    if (sigaction(SIGUSR2, &action, 0) == -1)
        return (-1);
    return (0);
}

//client --> usage : ./client <PID du server> <message>
int main(int argc, char **argv)
{
    int msg_error;
    
    if(argc < 3)
        return(ft_panic(argc));
    g_client.msg = argv[2];
	g_client.msg_len = ft_strlen(argv[2]);
	g_client.srv_pid = ft_atoi(argv[1]);
    g_client.flags = PONG_OK;
    g_client.bits_sent = 0;
    
    if (ft_set_sigaction() == -1)
		return (ft_panic(ACTION_FAIL));
    if (g_client.srv_pid <= 0)
		return (ft_panic(INVALID_PID));
	if (g_client.msg_len == 0)
		return (ft_panic(EMPTY_STR));
    msg_error = ft_send_msg(g_client.msg);
    if (msg_error != 0)
        return (ft_panic(SIG_ERROR));
   // printf("g_client.flags %d\n",g_client.flags);
    while (g_client.flags != MSG_R)
        pause();
	if (g_client.flags != MSG_R)
		return (ft_panic(NO_ROGER));
	if (g_client.flags == MSG_R)
		ft_putstr("Your message has been received by the server!", 1);
    return (0);
}