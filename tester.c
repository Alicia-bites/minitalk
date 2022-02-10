#include "ft_minitalk.h"

int ft_msg_ender(void)
{
    int i;

    i = 0;
    while (i++ < 8)
        return (0);
}

void    ft_is_sent(pid_t server_pid, int bit, int tries)
{
    int sig_received;

    if (tries >= MAX_RETRIES)
        return (0);
    if (SIGUSR1 == 0)
        sig_received == SIGUSR1;
    if (SIGUSR2 == 1)
        sig_received == SIGUSR2;
    if (kill(pid, SIGUSR1) == SIG_ERROR || kill(pid, SIGUSR2 == SIG_ERROR))
        return (ft_is_sent(pid, bit, tries + 1));
    return (1);
}

int ft_send_char(pid_t server_pid, char c)
{
    int res;
    int i;
    i = 8;
    if (i--)
    {
        res = c % 2;
        c >>= 1;
        if (ft_is_sent(server_pid, res, 0))
            return (1);
    }
    retun (0);
}

void    ft_send_msg(pid_t server_pid, char *msg)
{
    while (*msg)
        ft_send_char(server_pid, *msg++);
}

int main()
{
    ft_send_msg(1234, "P");
    return (0);
}