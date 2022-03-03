/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minitalk.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:16:36 by amarchan          #+#    #+#             */
/*   Updated: 2022/03/02 13:23:28 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MINITALK_H
# define FT_MINITALK_H

# define MAX_RETRIES 20

# define SIG_ERROR -1
# define ACTION_FAIL -2
# define INVALID_PID -3
# define EMPTY_STR -4
# define NO_ROGER -5
# define SRV_TIMEOUT -6
# define SIGACT_FAIL -7

# include <stdio.h>
# include <string.h>
# include <sys/types.h>
# include <signal.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>

typedef struct s_lined_up
{
	int					bit;
	pid_t				pid;
	int					srv_flag;
	struct s_lined_up	*prev;
	struct s_lined_up	*next;
}	t_lined_up;

typedef struct s_client
{
	char		*msg;
	size_t		msg_len;
	pid_t		srv_pid;
	uint8_t		flags;
	int			bits_sent;
}	t_client;

enum e_client_flags
{
	MSG_R=1,
	PONG_OK=2,
	CHAR_SENT=3	
};

extern t_client		g_client;
extern t_lined_up	*g_pile;

t_lined_up	*ft_lstnew(int bit, pid_t pid);
int			ft_strlen(const char *s);
int			ft_atoi(const char *str);
void		ft_putchar(char c);
void		ft_putstr(char *s, int isend);
void		ft_putnbr(int n);
void		ft_lstadd_back(t_lined_up **first_elt, t_lined_up *new);
int			ft_lstsize(t_lined_up *lst);
void		ft_lstclear(t_lined_up **lst);
void		ft_lstclear_back(t_lined_up **lst);
int			ft_msg_ender(void);
char 		*ft_strcat(char *dest, char *src);
int			ft_panic(int errcode);
int			ft_send_bit(int bit, int tries);
void		ft_quit(int signum, siginfo_t *info, void *context);
int			ft_null_byte(void);
int			ft_isdigit(int c);
int 		pid_is_valid(char *s);

#endif