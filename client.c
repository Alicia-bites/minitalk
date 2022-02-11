#include "ft_minitalk.h"

//termine le message du client par un '\0' soit 8 bits à 0
int ft_msg_ender(pid_t server_pid)
{
    int i;

    i = 0;
    while (i++ < 8)
        if (ft_is_sent(server_pid, 0, 0))
            return (1);
    return (0);
}

//verifie que le PID entre en parametre est compose uniquement de chiffres
int pid_is_valid(char *s)
{
    while (*s)
        if (!ft_isdigit(*s++))
		    return (0);
	return (1);
}

//envoie chaque bit et verifie que chaque bit a bien ete recu par le serveur
int    ft_is_sent(pid_t server_pid, int bit, int tries)
{
    int bit_sent;

    if (tries >= MAX_RETRIES)
        return (0);
    if (bit == 1)
        bit_sent = SIGUSR1;
    if (bit == 0)
        bit_sent = SIGUSR2;
    if (kill(server_pid, SIGUSR1) == SIG_ERROR || kill(server_pid, SIGUSR2 == SIG_ERROR))
        return (ft_is_sent(server_pid, bit, tries + 1));
    return (1);
}

// envoie chaque caractere bit par bit en commencant par le bit le plus faible
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
    return (0);
}

//recupere le message du client et l'envoie caractere par caractere a ft_send_char
int    ft_send_msg(pid_t server_pid, char *msg)
{
    while (*msg)
    {
        if (ft_send_char(server_pid, *msg++))
            return (1);
        pause();
    }
    ft_msg_ender(server_pid);
    return (0);
}

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
    server_pid = ft_atoi((argv[1]));
    sigaction(SIGUSR1, &action, 0);
    sigaction(SIGUSR2, &action, 0);
    if (!ft_send_msg(server_pid, argv[2]))
        ft_putstr("Unable to send message", 1);
    return(0);
}