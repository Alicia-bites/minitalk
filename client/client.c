#include "../headers/ft_minitalk.h"

t_client	g_client;

//envoie chaque bit et verifie que chaque bit a bien ete recu par le serveur
int    ft_send_bit(pid_t server_pid, int bit, int tries)
{
    int bit_sent;

    if (tries >= MAX_RETRIES)
        return (SIG_ERROR);
    if (bit == 1)
        bit_sent = SIGUSR1;
    if (bit == 0)
        bit_sent = SIGUSR2;
    if (kill(server_pid, bit_sent) == SIG_ERROR)
        ft_send_bit(server_pid, bit, tries + 1);
}

// envoie chaque caractere bit par bit en commencant par le bit le plus fort
int ft_send_char(pid_t server_pid, char c)
{
    int res;
    static int i = 7;
    
    //printf("i : %d\n", i);
    while (i >= 0)
    {
        res = (c >> i--) & 1;
        if (ft_send_bit(server_pid, res, 0) == SIG_ERROR)
            return (SIG_ERROR);
        g_client.flags = 0;
        usleep(500);
    }
    return (0);
}

//get client msg string and send it char by char to ft_send_char
int    ft_send_msg(pid_t server_pid, char *msg)
{
    while (*msg && g_client.flags & MSG_ACK)
        if (ft_send_char(server_pid, *msg++) == SIG_ERROR)
        {
            return (SIG_ERROR);
            usleep(500);
        }
            
    if (g_client.flags & MSG_ACK)
    {
        if (ft_msg_ender(server_pid) == SIG_ERROR)
        return (SIG_ERROR);
        usleep(500);
    }
        
    return (0);
}

void	handler(int signum)
{
	if (signum == SIGUSR1)
    {
        g_client.flags |= MSG_ACK;
        if (ft_send_msg(g_client.srv_pid, g_client.msg) == SIG_ERROR);
            g_client.flags |= NO_PING;
            
    }
		
}

//set up sigaction. When signal SIGUSR1 received --> send next bit
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
        return(ft_panic(argc));
    g_client.msg = argv[2];
	g_client.msg_len = ft_strlen(argv[2]);
	g_client.srv_pid = ft_atoi(argv[1]);
    g_client.flags = 1;
    
    if (ft_set_sigaction() == -1)
		return (ft_panic(ACTION_FAIL));
    if (g_client.srv_pid <= 0)
		return (ft_panic(INVALID_PID));
	if (g_client.msg_len == 0)
		return (ft_panic(EMPTY_STR));
    msg_error = ft_send_msg(g_client.srv_pid, g_client.msg);
    if (msg_error != 0)
        return (ft_panic(SIG_ERROR));
    usleep(500);
	if (!(g_client.flags & MSG_ACK))
		return (ft_panic(NO_ROGER));
	else
		ft_putstr("Your message has been delivered successfully!", 1);
    return (0);
}