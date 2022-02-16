#include "ft_minitalk.h"

void ft_send_char(pid_t server_pid, char c)
{
    int res;
    int i;
    i = 7;
    while (i >= 0)
    {
        res = (c >> i--) & 1;
        printf("%d", res);
    }
    puts("");
}

int main()
{
    ft_send_char(1234, 'a');
    return (1);
}