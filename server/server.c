
#include "../headers/ft_minitalk.h"
t_lined_up *g_pile = NULL;

// envoie un message "bien recu" si le serveur a bien recu le bit envoye par le client
int ft_roger(pid_t pid, int tries)
{
	if (tries == MAX_RETRIES)
		return (SIG_ERROR);
	if (kill(pid, SIGUSR1) == SIG_ERROR)
		ft_roger(pid, tries + 1);
}

//recupere les bits ranges dans la liste chainee et les transforme en char
char ft_built_char()
{ 
	int i;
	unsigned char c;
	t_lined_up *iterator;

	iterator = g_pile;
	i = 0;
	c = 0;
	while (i <= 7 && iterator->next) 
	{
		c += (iterator->bit << i++);
		iterator = iterator->next;
	}
	return (c);
}

// range chaque bit recu dans une liste chainee, confirme reception du bit
void ft_receive_bits(int signum, siginfo_t *info, void *context)
{
	t_lined_up *new;
	int count_bits;

	(void)context;
	if (signum == SIGUSR1)
		new = ft_lstnew(1, info->si_pid);
	if (signum == SIGUSR2)
		new = ft_lstnew(0, info->si_pid);
	ft_lstadd_back(&g_pile, new);
	if (ft_roger(info->si_pid, 0) == SIG_ERROR)
		return ;
	if (ft_lstsize(g_pile) == 8)
		ft_putchar(ft_built_char());
}

int main(int argc, char **argv)
{
	struct sigaction action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = ft_receive_bits;
	if (argc != 1)
		ft_putstr("No parameters needed", 1);
	ft_putstr("server pid : ", 0);
	ft_putnbr(getpid());
	ft_putchar('\n');
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (1)
		pause();
	return (1);
}