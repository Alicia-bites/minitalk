#include "headers/ft_minitalk.h"

t_client	g_client;

//envoie chaque bit et verifie que chaque bit a bien ete recu par le serveur
int    ft_is_sent(pid_t server_pid, int bit, int tries)
{
    int bit_sent;

    if (tries >= MAX_RETRIES)
        return (INVALID_PID);
    if (bit == 1)
        bit_sent = SIGUSR1;
    if (bit == 0)
        bit_sent = SIGUSR2;
    if (kill(server_pid, SIGUSR1) == SIG_ERROR || kill(server_pid, SIGUSR2 == SIG_ERROR))
        return (ft_is_sent(server_pid, bit, tries + 1));
    return (0);
}

// envoie chaque caractere bit par bit en commencant par le bit le plus fort
int ft_send_char(pid_t server_pid, char c)
{
    int res;
    int i;
    i = 8;
    if (i--)
    {
        res = c % 2;
        c >>= 1;
        if (ft_is_sent(server_pid, res, 0) == SIG_ERROR)
            return (INVALID_PID);
        usleep(2000);
    }
    return (0);
}

//recupere le message du client et l'envoie caractere par caractere a ft_send_char
int    ft_send_msg(pid_t server_pid, char *msg)
{
    while (*msg)
    {
        if (ft_send_char(server_pid, *msg++) == SIG_ERROR)
            return (-1);
        pause();
    }
    ft_msg_ender(server_pid);
    return (0);
}

void	handler(int signum)
{
	if (signum == SIGUSR1)
		ft_send_msg(g_client.srv_pid, g_client.msg);
}

//set up sigaction. A reception du signal SIGUSR1 : envoie next bit
int ft_set_sigaction (void)
{
    struct sigaction action;

    sigemptyset(&action.sa_mask);
    action.sa_sigaction = NULL;
    action.sa_handler = &handler;
    if (sigaction(SIGUSR1, &action, 0) == -1)
        return (-1);
    return (0);
}

//client --> usage : ./client <PID du server> <message>
int main(int argc, char **argv)
{
    int msg_error;

    if(argc < 3)
        ft_panic(argc);
    g_client.msg = argv[2];
	g_client.msg_len = ft_strlen(argv[2]);
	g_client.srv_pid = ft_atoi(argv[1]);
    g_client.flags = 0;
    if (ft_set_sigaction() == -1)
		return (ft_panic(ACTION_FAIL));
    if (g_client.srv_pid <= 0)
		return (ft_panic(INVALID_PID));
	if (g_client.msg_len == 0)
		return (ft_panic(EMPTY_STR));
    msg_error = ft_send_msg(g_client.srv_pid, g_client.msg);
    if (msg_error != 0)
        return (ft_panic(msg_error));
	usleep(500);
    return (0);
}