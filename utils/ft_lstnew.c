#include "../ft_minitalk.h"

t_lined_up	*ft_lstnew(int bit, pid_t pid)
{
	t_lined_up	*elt;

	elt = malloc(sizeof(t_lined_up));
	if (!elt)
		return (NULL);
	elt->bit = bit;
	elt->pid = pid;
	elt->next = NULL;
	return (elt);
}