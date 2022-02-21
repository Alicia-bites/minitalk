#include "../headers/ft_minitalk.h"

t_client	g_client;

//envoie chaque bit et verifie que chaque bit a bien ete recu par le serveur
int    ft_send_bit(int bit, int tries)
{
    int bit_sent;

    if (tries >= MAX_RETRIES)
        return (SIG_ERROR);
    if (bit == 1)
        bit_sent = SIGUSR1;
    if (bit == 0)
        bit_sent = SIGUSR2;
    printf("bit_sent : %d\n", bit);
    if (kill(g_client.srv_pid, bit_sent) == SIG_ERROR)
        ft_send_bit(bit, tries + 1);
}

// envoie chaque caractere bit par bit en commencant par le bit le plus fort
int ft_send_char(char c)
{
    int res = 0;
    static int i = 7;
    
    printf("g_client.flags : %d\n", g_client.flags);
    while (i >= 0 && g_client.flags == PONG_OK)
    {
        //printf("%d\n", i);
        res = (c >> i--) & 1;
        //printf("res : %d\n", res);
        g_client.flags = 0;
        if (ft_send_bit(res, 0) == SIG_ERROR)
            return (SIG_ERROR);
        usleep(10000);
    }
    return (0);
}

//get client msg string and send it char by char to ft_send_char
int    ft_send_msg(char *msg)
{
    int i;

    i = 0;
    while (msg[i])
    {
        //printf("msg: %c\n", msg[i]);
        if (ft_send_char(msg[i]) == SIG_ERROR)
            return (SIG_ERROR);
        i++;
    }
    if (*msg = '\0' && g_client.flags == PONG_OK)
        if (ft_msg_ender() == SIG_ERROR)
            return (SIG_ERROR);
    return (0);
}

//When SIGUSR1 is received, place the mask MSG_ACK and call ft_send_msg to send next bit
void	handler(int signum)
{
	if (signum == SIGUSR1)
    {
        ft_send_msg(g_client.msg);
        g_client.flags = PONG_OK;
    }
    if (signum == SIGUSR2)
        g_client.flags = MSG_ACK;
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
    g_client.flags = PONG_OK;
    
    if (ft_set_sigaction() == -1)
		return (ft_panic(ACTION_FAIL));
    if (g_client.srv_pid <= 0)
		return (ft_panic(INVALID_PID));
	if (g_client.msg_len == 0)
		return (ft_panic(EMPTY_STR));
    msg_error = ft_send_msg(g_client.msg);
    //printf("msg_error : %d\n", msg_error);
    if (msg_error != 0)
        return (ft_panic(SIG_ERROR));
    // usleep(500);
	// if (!(g_client.flags & MSG_ACK))
	// 	return (ft_panic(NO_ROGER));
	// else
	// 	ft_putstr("Your message has been delivered successfully!", 1);
    // return (0);
}