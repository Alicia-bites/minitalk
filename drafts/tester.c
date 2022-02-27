#include "headers/ft_minitalk.h"

t_lined_up *g_pile;

// char ft_built_char()
// { 
// 	int i;
// 	unsigned char c;
// 	t_lined_up *iterator;

// 	iterator = g_pile;
// 	i = 0;
// 	c = 0;
// 	while (i <= 7 && iterator->next) 
// 	{
// 		c += (iterator->bit << i++);
// 		iterator = iterator->next;
// 	}
// 	return (c);
// }

void	ft_lstclear(t_lined_up **lst)
{
	t_lined_up	*iterator;
	t_lined_up	*prev;

	iterator = *lst;
	prev = NULL;
	while (iterator)
	{
		prev = iterator;
		iterator = iterator->next;
		free(prev);
	}
	*lst = NULL;
}

int main()
{

    t_lined_up *iterator;
    pid_t pid_test;
    int i;
    t_lined_up *new;

    i = 0;
    pid_test = 1234;
    
    while (i < 8)
    {
        new = ft_lstnew(1, pid_test++);
        ft_lstadd_back(&g_pile, new);
        i++;
    }
    iterator = g_pile;
    while (iterator)
    {
        printf("%d %d\n", iterator->bit, iterator->pid);
        iterator = iterator->next;
    }
    ft_lstclear(&g_pile);
    iterator = g_pile;
    while (iterator)
    {
        printf("%d %d\n", iterator->bit, iterator->pid);
        iterator = iterator->next;
    }
    return (0);
}