#include "minirt.h"

// add Ambient
int	add_ambient(t_mrt *mrt, t_ambient *node)
{
	t_ambient	*head;

	head = mrt->ambt;
	if (!head)
		mrt->ambt = node;
	else
	{
		while (head->next)
			head = head->next;
		head->next = node;
	}
	return (0);
}

// get ambient
int	get_ambient(t_mrt *mrt, char **attr, int unique)
{
	t_ambient	*ambt;

	if (mrt->ambt && (mrt->ambt->unique == 1 || unique == 1))
		return (elog("Ambient Duplicated", qcode(mrt, 1)));
	ambt = malloc(sizeof(t_ambient));
	if (!ambt)
		return (qcode(mrt, 1));
	ambt->ratio = getdouble(attr[1]);
	ambt->color = getvec3(mrt, attr[2], 255);
	free2(attr);
	checkvalue(mrt, ambt->ratio, 0, 1);
	checkvec3(mrt, ambt->color, 0, 1);
	if (mrt->qcode)
		return (elog("Ambient parsing fail", mrt->qcode));
	ambt->unique = unique;
	ambt->next = 0;
	add_ambient(mrt, ambt);
	printf("Ambient parsing completed\n");
	return (mrt->qcode);
}

// jsut check there is any that type of object in the loop
int	check_unique(t_mrt *mrt, int type, int unique)
{
	t_object	*head;

	head = mrt->obj;
	if (!mrt->obj)
		return (0);
	while (head)
	{
		if (head->type == type)
		{
			if (unique == 1 || head->unique == 1)
				return (qcode(mrt, 1));
		}
		head = head->next;
	}
	return (0);
}
