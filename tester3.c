#include "hearders/ft_minitalk.h"

int ft_send_char(pid_t server_pid, char c)
{
    int res;
    int i;
    i = 7;
    while (i >= 0)
    {
        res = (c >> i--) & 1;
        return (res);
    }
    puts("");
    return (0);
}

char ft_built_char(int tab[8])
{ 
    int i;
    unsigned char c;

    i = 7;
    c = 0;
    while (i >= 0)
        c += (tab[7-i] << i--);
    return (c);
}

int main()
{
    int i;

    i = 0;
    int tab[8];

    tab[0] = 0;
    tab[1] = 1;
    tab[2] = 1;
    tab[3] = 0;
    tab[4] = 0;
    tab[5] = 0;
    tab[6] = 0;
    tab[7] = 1;

    //printf("%d\n", ft_send_char(1234, 'a'));
    printf("%c\n", ft_built_char(tab));
    return (1);
}