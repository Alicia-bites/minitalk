
#include "ft_minitalk.h"

//envoie un message "bien recu" si le serveur a bien recu le bit envoye par le client
void    ft_roger(pid_t pid, int retry)
{
    int ntries;

    ntries = 0;
    if (tries == MAX_RETRIES)
        return ;
    if (kill(pid, SIGUSR1) == -1)
        ft_roger(pid, ntries + 1);
}

void    ft_print_msg(char* str)
{

}

int main(int argc, char **argv)
{
    ft_putstr("server pid : ", 0)
    ft_putnbr(getpid());
    ft_putchar('\n');
    sigaction()
    while (1);
    return (0);
}