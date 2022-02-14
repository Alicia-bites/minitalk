#include "ft_minitalk.h"

int    ft_is_sent(pid_t server_pid, int bit, int tries)
{
    int bit_sent;

    if (tries >= MAX_RETRIES)
        return (-1);
    if (bit == 1)
        bit_sent = SIGUSR1;
    if (bit == 0)
        bit_sent = SIGUSR2;
    if (kill(server_pid, SIGUSR1) == SIG_ERROR || kill(server_pid, SIGUSR2 == SIG_ERROR))
        return (ft_is_sent(server_pid, bit, tries + 1));
    return (0);
}

int main()
{
    ft_is_sent(1234, 0, 0);
    printf("%d\n", ft_is_sent(1234, 0, 0));
    return (0);
}