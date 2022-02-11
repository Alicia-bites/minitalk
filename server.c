
#include "ft_minitalk.h"

t_lined_up *g_line= NULL;

//envoie un message "bien recu" si le serveur a bien recu le bit envoye par le client
void    ft_roger(pid_t pid, int tries)
{
    if (tries == MAX_RETRIES)
        return ;
    if (kill(pid, SIGUSR1) == SIG_ERROR)
        ft_roger(pid, tries + 1);
}


char    *ft_built_msg(int signum, siginfo_t *info, void *context)
{
    t_lined_up  *new;
    int count_clients;

    (void) context;
    if (signum == SIGUSR1)
        new = ft_lstnew(1, info->si_pid);
    if (signum == SIGUSR2)
        new = ft_lstnew(0, info->si_pid);
    ft_lstadd_back(g_line, new);

}

void    ft_print_msg(char* str)
{


}

int main(int argc, char **argv)
{
    struct sigaction action;

    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = ft_built_msg();
    if (argc != 1)
        ft_putstr("No parameters needed", 1);
    ft_putstr("server pid : ", 0);
    ft_putnbr(getpid());
    ft_putchar('\n');
    sigaction(SIGUSR1, &action, 0);
    while (1)
        pause();
    return (1);
}