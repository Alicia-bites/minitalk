#include "../ft_minitalk.h"

int ft_valid_pid(pid)
{
    
}

//renvoie les msg d'erreurs appropries. 
// usage : ./client <PID> <msg>
void    ft_panic()
{
    char *source = "invalid PID";

    ft_putstr(source);
    ft_putstr(":");
    ft_putstr(message);
    
    if (if(isdigit(pid))
        ft_putstr("invalid PID : PID must be digits only", 0);)
}

