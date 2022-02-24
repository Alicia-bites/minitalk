/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:16:22 by amarchan          #+#    #+#             */
/*   Updated: 2022/02/24 17:51:51 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_minitalk.h"
t_lined_up *g_pile;

//boolean that checks if there is a list of 8 consecutive zero in g_pile ->
//to see if null byte has been sent.
int	ft_null_byte()
{
	int	i;
	int count_bits;
	t_lined_up *iterator;

	count_bits = 0;
	iterator = g_pile;
	while (iterator)
	{
		if (count_bits % 8 == 0)
		{
			i = 0;
            while (iterator->bit == 0)
            {  
                i++;
                iterator = iterator->next;
                count_bits++;
                if (i == 7)
                    return (1);
            }
		}
		iterator = iterator->next;
        count_bits++;
	}
	return (0);
}

// envoie un message "bien recu" si le serveur a bien recu le bit envoye par le client
int ft_roger(pid_t pid, int *msg_received, int tries)
{
	int	signal;

	//printf("*msg_receveived : %d\n", *msg_received);
	if (tries == MAX_RETRIES)
		return (SIG_ERROR);
	if (*msg_received == 0)
		signal = SIGUSR1;
	if (*msg_received == 1)
		signal = SIGUSR2;
	if (kill(pid, signal) == SIG_ERROR)
		ft_roger(pid, msg_received, tries + 1);
	*msg_received = 0;
	return (0);
}

//recupere les bits ranges dans la liste chainee et les transforme en char
char ft_built_char(pid_t pid, int *msg_received)
{ 
	int i;
	unsigned char c;

	i = 0;
	c = 0;
	while (i <= 7 && g_pile) 
	{
		c += (g_pile->bit << 7-i++);
		g_pile = g_pile->next;
	}
	if (c == 0)
	{
		*msg_received = 1;
		if (ft_roger(pid, msg_received, 0) == SIG_ERROR)
		{
			ft_putstr("signal error, reception not aknowledged", 1);
			return (0);
		}
	}
	return (c);
}

void	ft_print_msg(pid_t pid, int *msg_received)
{
	ft_putchar(ft_built_char(pid, msg_received));
}

// range chaque bit recu dans une liste chainee, confirme reception du bit
void ft_receive_bits(int signum, siginfo_t *info, void *context)
{
	t_lined_up *new;
	int msg_received;
	static int count_bits = 0;

	(void)context;
	msg_received = 0;
	if (signum == SIGUSR1)
		new = ft_lstnew(1, info->si_pid);
	if (signum == SIGUSR2)
		new = ft_lstnew(0, info->si_pid);
	ft_lstadd_back(&g_pile, new);
	//printf("new->bit : %d\n", new->bit);
	if (ft_roger(info->si_pid, &msg_received, 0) == SIG_ERROR)
		return ;
	count_bits = ft_lstsize(g_pile);
	while (count_bits % 8 == 0 && ft_null_byte())
		ft_print_msg(info->si_pid, &msg_received);
}

void	ft_quit(int signum)
{
	(void) signum;
	ft_lstclear(&g_pile);
	exit(1);
}

static int ft_set_sigaction (void)
{
    struct sigaction action;

    sigemptyset(&action.sa_mask);
	action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = ft_receive_bits;
    if (sigaction(SIGUSR1, &action, 0) == -1)
        return (-1);
    if (sigaction(SIGUSR2, &action, 0) == -1)
        return (-1);
	sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    action.sa_sigaction = NULL;
	action.sa_handler = &ft_quit; 
	if (sigaction(SIGINT, &action, NULL) == -1)
		return (-1);

    return (0);
}

int main(int argc, char **argv)
{
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