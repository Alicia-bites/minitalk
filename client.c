#include "ft_minitalk.h"

int ft_msg_ender(void)
{
    int i;

    i = 0;
    while (i++ < 8)
        return (0);
}

//verifie que le PID entre en parametre est compose uniquement de chiffres
int pid_is_valid(char *s)
{
    if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

//envoie chaque bit et verifie que chaque bit a bien ete recu par le serveur
void    ft_is_sent(pid_t pid, int bit, int tries)
{
    int sig_received;

    if (tries >= MAX_RETRIES)
        return (0);
    if (SIGUSR1 = 0)
        sig_received == SIGUSR1;
    if (SIGUSR2 = 1)
        sig_received == SIGUSR2;
    if (kill(pid, SIGUSR1) == SIG_ERROR || kill(pid, SIGUSR2 == SIG_ERROR))
        return (ft_is_sent(pid, bit, tries + 1));
    return (1);
}

//recupere le message du client bit par bit en commencant par le bit le plus faible
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

int ft_get_pid(argv[1])
//client --> usage : ./client <PID du server> <message>
int main(int argc, char **argv)
{
    struct sigaction action;
    pid_t server_pid;

    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = ft_send_msg;
    sigemptyset(&action.sa_mask);
    if(argc != 3)
        ft_putstr("Invalid number of arguments", 1);
    if (!pid_is_valid(argv[1]))
        ft_putstr("PID must be digit only", 1);
    server_pid = ft_get_pid(argv[1]);
    sigaction(SIGUSR1, &action, 0);
    sigaction(SIGUSR2, &action, 0);
    if (!ft_send_msg(server_pid, argv[2]))
        ft_putstr("Unable to send message", 1);
    return(0);
}