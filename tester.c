#include "ft_minitalk.h"

t_lined_up *g_pile;

int ft_count_clients(void)
{
    int n;
    t_lined_up *iterator;
    pid_t ex_pid;

    n = 1;
    ex_pid = 0;
    iterator = g_pile;
    while(iterator->next)
    {
        ex_pid = iterator->pid;
        iterator = iterator->next;
        if (ex_pid != iterator->pid)
            n++;
    }
    return (n);
}

int main()
{

    t_lined_up *iterator;
    pid_t pid_test;
    int i;
    t_lined_up *new;

    i = 0;
    pid_test = 1234;
    
    while (i < 3 && pid_test < 1237)
    {
        new = ft_lstnew(i++, pid_test++);
        ft_lstadd_back(&g_pile, new);
    }
    iterator = g_pile;
    while (iterator)
    {
        printf("%d %d\n", iterator->bit, iterator->pid);
        iterator = iterator->next;
    }
    printf("%d\n", ft_count_clients());
    return (0);
}