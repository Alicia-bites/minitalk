#include "../headers/ft_minitalk.h"

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

void	ft_lstadd_back(t_lined_up **first_elt, t_lined_up *new)
{
	t_lined_up	*iterator;

	iterator = *first_elt;
	if (first_elt && new)
	{
		if (!*first_elt)
			*first_elt = new;
		else
		{	
			while (iterator->next)
                iterator = iterator->next;
			iterator->next = new;
            new->prev = iterator;
            // printf("new %p\n", new);
            // printf("iterator->prev %p\n", iterator->prev);
		}
	}
}

//clear the list starting from the LAST element
void	ft_lstclear_back(t_lined_up **lst)
{
	t_lined_up	*iterator;
	t_lined_up	*prev;

	iterator = *lst;
	prev = NULL;
	while (iterator->prev)
	{
		prev = iterator;
		iterator = iterator->prev;
        // printf("g_pile : %p\n", g_pile);
		free(prev);
	}
    free(iterator);
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
    
    while (i < 4)
    {
        new = ft_lstnew(1, pid_test++);
        ft_lstadd_back(&g_pile, new);
        i++;
    }
    g_pile;
    while (g_pile->next)
    {
        printf("g_pile : %p\n", g_pile);
        g_pile = g_pile->next;
    }
    ft_lstclear_back(&g_pile);
    // puts("-----------------");
    // iterator = g_pile;
    // while (iterator)
    // {
    //     printf("%p\n", iterator);
    //     iterator = iterator->prev;
    // }
    return (0);
}