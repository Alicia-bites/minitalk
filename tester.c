#include "ft_minitalk.h"

int ft_get_pid(char *char_pid)
{
    
    return (ft_atoi(char_pid));
}

int main()
{
    pid_t server_pid;

    server_pid = ft_get_pid("01234");
    printf("%d\n", server_pid);
    return (0);
}