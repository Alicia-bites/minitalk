#ifndef FT_MINITALK_H
# define FT_MINITALK_H

# define MAX_RETRIES 20

# define SIG_ERROR -1
# define ACTION_FAIL -2
# define INVALID_PID -3
# define EMPTY_STR -4
# define NO_COM -5
# define SRV_TIMEOUT -6
# define SIGACT_FAIL -7

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdint.h>
#include <stdlib.h>

typedef struct s_lined_up
{
	int	  				bit;
	pid_t 				pid;
	struct s_lined_up	*next;
}	t_lined_up;

typedef struct s_client
{
	char		*msg;
	size_t		msg_len;
	pid_t		srv_pid;
	uint8_t		flags;
}	t_client;

enum client_flag
{
	MSG_RECEIVED = 0x01,
	BIT_RECEIVED = 0x02,
};

extern t_client		g_client;
extern t_lined_up	*g_pile;

t_lined_up	*ft_lstnew(int bit, pid_t pid);
void		ft_lstadd_back(t_lined_up **first_elt, t_lined_up *new);
void    	ft_roger(pid_t pid, int tries);
void    	ft_receive_bits(int signum, siginfo_t *info, void *context);
int 		ft_msg_ender(pid_t server_pid);
void		ft_putchar(char c);
void		ft_putstr(char *s, int isend);
void		ft_putnbr(int n);
int	    	ft_atoi(const char *str);
int	    	ft_isdigit(int c);
int	    	ft_strlen(const char *s);
int 		pid_is_valid(char *s);
int    		ft_panic(int errcode);
int    		ft_is_sent(pid_t server_pid, int bit, int tries);
int 		t_send_char(pid_t server_pid, char c);
int    		ft_send_msg(pid_t server_pid, char *msg);

# endif