#include "minirt.h"

int	elog(char *str, int res)
{
	printf("Error\n%s\n", str);
	return (res);
}

int	free2(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
	return (0);
}

int	freelist(t_list *list)
{
	t_list	*head;

	head = list;
	if (!head)
		return (0);
	while (head)
	{
		head = head->next;
		free(list);
		list = head;
	}
	list = 0;
	return (0);
}

int	clean(t_mrt *mrt, int res)
{
	if (mrt->ambt)
		freelist((t_list *)mrt->ambt);
	if (mrt->cam)
		freelist((t_list *)mrt->cam);
	if (mrt->lght)
		freelist((t_list *)mrt->lght);
	if (mrt->obj)
		freelist((t_list *)mrt->obj);
	return (res);
}
