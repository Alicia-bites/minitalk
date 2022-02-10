
#include "ft_minitalk.h"

//envoie un message "bien recu" si le serveur a bien recu le bit envoye par le client
void    ft_roger(pid_t pid, int tries)
{
    int tries;

    tries = 0;
    if (tries == MAX_RETRIES)
        return ;
    if (kill(pid, SIGUSR1) == SIG_ERROR)
        ft_roger(pid, tries + 1);
}
char    *ft_built_msg()
{

}

void    ft_print_msg(char* str)
{

}

int main(int argc, char **argv)
{
    if (argc != 1)
        ft_putstr("No param needed", 1);
    ft_putstr("server pid : ", 0)
    ft_putnbr(getpid());
    ft_putchar('\n');
    sigaction(SIGUSR1, )
    while (1);
        pause();
    return (1);
}