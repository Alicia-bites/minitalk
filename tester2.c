#include "headers/ft_minitalk.h"

t_lined_up *g_pile = NULL;

int	ft_null_byte(t_lined_up *g_pile)
{
	t_lined_up *iterator;
	int	i;

	iterator = g_pile;
	i = 7;
	while (i-- >= 0 && iterator)
		if (iterator->bit != 0)
			return (-1);
	return (0);
}

int main()
{

    t_lined_up *iterator;
    pid_t pid_test;
    int i;
    t_lined_up *new;

    i = 0;
    pid_test = 1234;
    
    while (i < 8)
    {
        new = ft_lstnew(1, pid_test++);
        ft_lstadd_back(&g_pile, new);
        i++;
    }
    // iterator = g_pile;
    // while (iterator)
    // {
    //     printf("%d %d\n", iterator->bit, iterator->pid);
    //     iterator = iterator->next;
    // }
    printf("%d\n", ft_null_byte(g_pile));
    return (0);
}