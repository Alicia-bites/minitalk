#include "minitalk.h"

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

int main()
{
    
}