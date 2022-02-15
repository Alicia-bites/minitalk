#include "ft_minitalk.h"

// compte le nombre de PID uniques dans la liste chainee 
int ft_count_clients(void)
{
    int n;
    pid_t ex_pid;

    n = 0;
    while(g_pile)
    {
        ex_pid = g_pile->pid;
        g_pile = g_pile->next;
        if (ex_pid != g_pile->pid)
            n++;
    }
    return (n);
}