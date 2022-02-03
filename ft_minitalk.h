#ifndef FT_MINITALK_H
# define FT_MINITALK_H

#ifndefine MAX_RETRIES
# define MAX_RETRIES 20
# endif

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>


void    ft_roger(pid_t pid, int retry);
void    ft_send_bit(pid_t pid, int retry);
void	ft_putstr(char *s, int isend);
void	ft_putchar(char c);
int	    ft_atoi(const char *str);
int	    ft_isdigit(int c);



#endif