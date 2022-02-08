//envoie le message bit par bit au serveur
int pid_is_valid(char *s)
{
    if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void    ft_is_sent(int pid, int bit, int tries)
{
    int sig_received;

    if (tries >= MAX_RETRIES)
        return (1);
    if (SIGUSR1 = 0)
        sig_received = SIGUSR1;
    if (SIGUSR2 = 1)
        sig_received = SIGUSR2;
    if (kill(pid, SIGUSR1) == -1 || kill(pid, SIGUSR2 == -1)
        return ft_is_sent(pid, bit, tr + 1);
    return (0);
}

void    ft_send_msg(char *msg)
{

}

int main(int argc, char **argv)
{
    if(argc != 3)
        ft_putstr("Invalid number of arguments", 1);
    if (!pid_is_valid(argv[1]))
        ft_putstr("PID must be digit only", 1);
    
    if (!ft_send_msg(getpid(argv[1]), argv[2]))
        ft_putstr("Unable to send message", 1);
}