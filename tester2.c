#include "headers/ft_minitalk.h"

t_lined_up *g_pile = NULL;

// int	ft_null_byte()
// {
// 	t_lined_up *iterator;
// 	int	i;

// 	iterator = g_pile;
// 	i = 7;
// 	printf("interator->bit : %d\n", iterator->bit);
// 	while (i-- >= 0 && iterator)
// 	{
// 		if (iterator->bit != 0)
// 			return (0);
// 		printf("interator->bit : %d\n", iterator->bit);
// 		iterator = iterator->next;
// 	}
// 	return (1);
// }

int	ft_null_byte()
{
	int	i;
	int count_bits;
	t_lined_up *iterator;

	count_bits = 0;
	iterator = g_pile;
	while (iterator)
	{
		if (count_bits % 8 == 0)
		{
			i = 0;
            while (iterator->bit == 0)
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

// int	ft_null_byte()
// {
// 	int	i;
// 	int count;
// 	t_lined_up *iterator;

//     i = 0;
//     count = 0;
//     iterator = g_pile;
//     while (iterator)
//     {
//         if (iterator->bit == 0)
//             i++;
//         if (i == 7 && count % 8 == 0)
//             return (1);
//         printf("%d\n", i);
//         iterator = iterator->next;
//         count++;
//     }
//     return (0);
// }

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
    i = 0;
    while (i < 4)
    {
        new = ft_lstnew(0, pid_test++);
        ft_lstadd_back(&g_pile, new);
        i++;
    }
    i = 0;
    while (i < 4)
    {
        new = ft_lstnew(0, pid_test++);
        ft_lstadd_back(&g_pile, new);
        i++;
    }
    i = 0;
    while (i < 4)
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
    printf("%d\n", ft_null_byte());
    return (0);
}