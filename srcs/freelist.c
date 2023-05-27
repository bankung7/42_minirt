#include "minirt.h" 

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
