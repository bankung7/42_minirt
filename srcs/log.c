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

int	freelista(t_ambient *list)
{
	t_ambient	*head;

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

int	freelistc(t_camera *list)
{
	t_camera	*head;

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

int	freelistl(t_light *list)
{
	t_light	*head;

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

int	freelisto(t_object *list)
{
	t_object	*head;

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
		freelista(mrt->ambt);
	if (mrt->cam)
		freelistc(mrt->cam);
	if (mrt->lght)
		freelistl(mrt->lght);
	if (mrt->obj)
		freelisto(mrt->obj);
	return (res);
}
