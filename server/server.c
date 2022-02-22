
#include "../headers/ft_minitalk.h"
t_lined_up *g_pile = NULL;

//check if there is a list of 8 consecutive zero in g_pile ->
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
int ft_roger(pid_t pid, int tries)
{
	if (tries == MAX_RETRIES)
		return (SIG_ERROR);
	if (kill(pid, SIGUSR1) == SIG_ERROR)
		ft_roger(pid, tries + 1);
	return (0);
}

//recupere les bits ranges dans la liste chainee et les transforme en char
char ft_built_char()
{ 
	int i;
	unsigned char c;

	i = 0;
	c = 0;
	while (i <= 7 && g_pile) 
	{
		c += (g_pile->bit << 7-i++);
		//printf("g_pile->bit: %d\n", g_pile->bit);
		g_pile = g_pile->next;
	}
	return (c);
}

// void	ft_print_pile()
// {
// 		ft_putchar(ft_built_char());
// }

// range chaque bit recu dans une liste chainee, confirme reception du bit
void ft_receive_bits(int signum, siginfo_t *info, void *context)
{
	t_lined_up *new;
	static int count_bits = 0;
	int	go_print;
	t_lined_up *iterator;

	(void)context;
	if (signum == SIGUSR1)
		new = ft_lstnew(1, info->si_pid);
	if (signum == SIGUSR2)
		new = ft_lstnew(0, info->si_pid);
	ft_lstadd_back(&g_pile, new);
	printf("new->bit : %d\n", new->bit);
	count_bits = ft_lstsize(g_pile);
	while (count_bits % 8 == 0 && ft_null_byte())
		ft_putchar(ft_built_char());
	if (ft_roger(info->si_pid, 0) == SIG_ERROR)
		return ;
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