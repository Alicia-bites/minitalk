#include "ft_minitalk.h"

int    ft_is_sent(int pid, int bit, int tries)
{
    int sig_received;

    if (tries >= MAX_RETRIES)
        return (0);
    if (SIGUSR1 == 0)
        sig_received = SIGUSR1;
    if (SIGUSR2 == 1)
        sig_received = SIGUSR2;
    if (kill(pid, SIGUSR1) == SIG_ERROR || kill(pid, SIGUSR2 == SIG_ERROR))
        return (ft_is_sent(pid, bit, tries + 1));
    return (1);
}

int main()
{
    printf("%d\n", ft_is_sent(12345, 0, 0));
    return (0);
}