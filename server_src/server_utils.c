/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amarchan <amarchan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 14:16:11 by amarchan          #+#    #+#             */
/*   Updated: 2022/03/02 10:16:15 by amarchan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/ft_minitalk.h"

//clean before when sudden exit (SIGINT)
void	ft_quit(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (signum == SIGINT)
	{
		if (!g_pile)
		{
			ft_putstr("Nothing else to clean!", 1);
			exit(EXIT_SUCCESS);
		}
		ft_lstclear_back(&g_pile);
		ft_putstr("g_pile cleaned", 1);
		exit(1);
	}
}

//boolean that checks if there is a list of 8 consecutive zero in g_pile ->
//to see if null byte has been sent.
int	ft_null_byte(void)
{
	int			i;
	int			count_bits;
	t_lined_up	*iterator;

	count_bits = 0;
	iterator = g_pile;
	while (iterator)
	{
		if (count_bits % 8 == 0)
		{
			i = 0;
			while (iterator->next && iterator->bit == 0)
			{
				i++;
				iterator = iterator->next;
				count_bits++;
				if (i == 7)
					return (1);
			}
		}
		iterator = iterator->next;
		count_bits++;
	}
	return (0);
}
