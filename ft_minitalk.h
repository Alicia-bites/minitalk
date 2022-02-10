#ifndef FT_MINITALK_H
# define FT_MINITALK_H

# define MAX_RETRIES 20
# define SIG_ERROR -1

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

void    ft_roger(pid_t pid, int retry);
void    ft_send_bit(pid_t pid, int retry);
void	ft_putchar(char c);
void	ft_putstr(char *s, int isend);
void	ft_putnbr(int n);
int	    ft_atoi(const char *str);
int	    ft_isdigit(int c);
int	    ft_strlen(const char *s);
int     sigaction(int signum, const struct sigaction *act,
              struct sigaction *oldact);

# endif