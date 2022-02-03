
#include "ft_minitalk.h"

//envoie un message "bien recu" si le serveur a bien recu le bit envoye par le client
void    ft_roger(pid_t pid, int retry)
{
    int i;

    i = 0;
    while(i < MAX_RETRIES)
    {
        kill(pid, SIGUSR1);
        ft_roger(pid, retry + 1);
        i++;
    }
}

int main(int argc, char **argv)
{
    t_pid   server_pid;

    server_pid = getpid(void);
}