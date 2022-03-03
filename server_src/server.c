/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:16:22 by amarchan          #+#    #+#             */
/*   Updated: 2022/03/03 19:12:47 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_minitalk.h"

t_lined_up	*g_pile;

//Send aknownledgment to client that bit has been received
int	ft_roger(pid_t pid, int *msg_received, int tries)
{
	int		signal;

	if (tries == MAX_RETRIES)
		return (SIG_ERROR);
	if (*msg_received == 0)
		signal = SIGUSR1;
	if (*msg_received == 1)
		signal = SIGUSR2;
	// printf("signal sent : %d\n", signal);
	if (kill(pid, signal) == SIG_ERROR)
		ft_roger(pid, msg_received, tries + 1);
	*msg_received = 0;
	return (0);
}

//Get bits from linked list and build char
char	ft_built_char(pid_t pid, int *msg_received)
{
	int				i;
	unsigned char	c;

	i = 0;
	c = 0;
	while (i <= 7 && g_pile->next)
	{
		c += (g_pile->bit << (7 - i++));
		g_pile = g_pile->next;
	}
	if (c == 0)
	{
		*msg_received = 1;
		ft_lstclear_back(&g_pile);
		if (ft_roger(pid, msg_received, 0) == SIG_ERROR)
		{
			ft_putstr("signal error, reception not aknowledged", 1);
			return (0);
		}
	}
	return (c);
}

//Add every bit in a linked list, send confirmation to client
void	ft_receive_bits(int signum, siginfo_t *info, void *context)
{
	t_lined_up	*new;
	int			msg_received;
	static int	count_bits = 0;
	static int	new_pid = 0;

	(void)context;
	usleep(10);
	// printf("info->si_pid : %d\n", info->si_pid);
	if (info->si_pid != new_pid)
		ft_lstclear(&g_pile);
	msg_received = 0;
	if (signum == SIGUSR1)
		new = ft_lstnew(1, info->si_pid);
	if (signum == SIGUSR2)
		new = ft_lstnew(0, info->si_pid);
	// printf("new->bit%d\n", new->bit);
	ft_lstadd_back(&g_pile, new);
	new_pid = info->si_pid;
	if (ft_roger(info->si_pid, &msg_received, 0) == SIG_ERROR)
		return ;
	usleep(100);
	count_bits = ft_lstsize(g_pile);
	while (count_bits % 8 == 0 && ft_null_byte())
		ft_putchar(ft_built_char(info->si_pid, &msg_received));
}

//Set up signal catcher function 
//for SIGUSR1, SIGUSR2 and SIGINT
static int	ft_set_sigaction(void)
{
	struct sigaction	action;

	action.sa_sigaction = ft_receive_bits;
	action.sa_flags = SA_SIGINFO;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGUSR1);
	sigaddset(&action.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &action, 0) == -1)
		return (-1);
	if (sigaction(SIGUSR2, &action, 0) == -1)
		return (-1);
	action.sa_sigaction = ft_quit;
	action.sa_flags = SA_SIGINFO;
	sigemptyset(&action.sa_mask);
	sigaddset(&action.sa_mask, SIGINT);
	if (sigaction(SIGINT, &action, 0) == -1)
		return (-1);
	return (0);
}

//print server PID and wait for client message
int	main(int argc, char **argv)
{
	(void) argv;
	if (ft_set_sigaction() == -1)
		ft_putstr("Setting up sigaction failed.", 1);
	if (argc != 1)
		ft_putstr("No parameters needed", 1);
	ft_putstr("server pid : ", 0);
	ft_putnbr(getpid());
	ft_putchar('\n');
	while (1)
		pause();
	return (1);
}
