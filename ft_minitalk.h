#ifndef FT_MINITALK_H
# define FT_MINITALK_H

# define MAX_RETRIES 20
# define SIG_ERROR -1

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

typedef struct s_lined_up
{
	int	  				bit;
	pid_t 				pid;
	struct s_lined_up	*next;
}	t_lined_up;

t_lined_up	*ft_lstnew(int bit, pid_t pid);
void		ft_lstadd_back(t_lined_up **first_elt, t_lined_up *new);
void    	ft_roger(pid_t pid, int tries);
char    	*ft_built_msg(int signum, siginfo_t *info, void *context);
int 		t_msg_ender(pid_t server_pid);
void		ft_putchar(char c);
void		ft_putstr(char *s, int isend);
void		ft_putnbr(int n);
int	    	ft_atoi(const char *str);
int	    	ft_isdigit(int c);
int	    	ft_strlen(const char *s);
int 		pid_is_valid(char *s);
int    		ft_is_sent(pid_t server_pid, int bit, int tries);
int 		t_send_char(pid_t server_pid, char c);
int    		ft_send_msg(pid_t server_pid, char *msg);

# endif