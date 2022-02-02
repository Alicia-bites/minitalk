
//envoie un message "bien recu"
void    ft_roger(pid, retry)
{
    int i;

    i = 0;
    while(i < MAX_TRIES)
    {
        kill(pid, SIGUSR1);
        ft_roger(pid, retry);
    }
}