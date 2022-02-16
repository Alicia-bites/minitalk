#include "ft_minitalk.h"

int    ft_panic(int errcode)
{
    if (errcode == 1)
        ft_putstr("Missing PID and message", 1);
    else if (errcode == 2)
        ft_putstr("Missing PID or message.", 1);
    else if (errcode == SIGACT_FAIL)
        ft_putstr("Setting up sigaction failed.", 1);
    else if (errcode == INVALID_PID)
        ft_putstr("Invalid PID. PID must be digits only", 1);
    else if (errcode == EMPTY_STR)
        ft_putstr("Empty string.", 1);
    else if (errcode == NO_COM)
        ft_putstr("Message not sent", 1);
    else if (errcode == SRV_TIMEOUT)
        ft_putstr("Impossible to reach server", 1);
    return (errcode);
}

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