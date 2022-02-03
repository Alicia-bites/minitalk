//envoie le message bit par bit au serveur
void    ft_send_bit(pid_t pid, int retry)
{
    int i;
    int signal;

    i = 0;
    if (SIGUSR1 = 0)
        signal = SIGUSR1;
    if (SIGUSR2 = 1)
        signal = SIGUSR2;
    while (i < MAX_RETRIES)
    {
        if (kill(pid, SIGUSR1) == -1 || kill(pid, SIGUSR2 == -1)
            ft_panic()
        ft_send_msg(pid, retry + 1);
        i++;
    }
}

int main(int argc, char **argv)
{
    if(argc == 3)
    {
        ft_get_pid(argv[1]);
        ft_get_msg(argv[2]);
        ft_send_bit(argv[1], argv[2]);
    }
    ft_putstr("invalid number of arguments", 1);
}