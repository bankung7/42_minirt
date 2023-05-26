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
int getAmbient(t_mrt *mrt, char **attr, int unique)
{
    t_ambient *ambt;

    if (mrt->ambt && mrt->ambt->unique == 1)
	{
		printf("Dulicated!!\n");
        return (free2(attr));
	}
    if (mrt->ambt && !ft_strncmp(attr[0], "A", 2))
        freelist((t_list*)mrt->ambt);
    ambt = malloc(sizeof(t_ambient));
    if (!ambt)
        return (qCode(mrt, 1));
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
