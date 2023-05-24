#include "minirt.h"

// add Ambient
int addAmbient(t_mrt *mrt, t_ambient *node)
{
    t_ambient *head;

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
        return (free2(attr));
    if (mrt->ambt && !ft_strncmp(attr[0], "A", 2))
        freeList((t_list*)mrt->ambt);
    ambt = malloc(sizeof(t_ambient));
    if (!ambt)
        return (qCode(mrt, 1));
    ambt->ratio = getDouble(attr[1]);
    ambt->color = getVec3(mrt, attr[2], 255);
    free2(attr);
    checkValue(mrt, ambt->ratio, 0, 1);
    checkVec3(mrt, ambt->color, 0, 1);
    if (mrt->qcode)
        return (elog("Ambient parsing fail", mrt->qcode));
    ambt->unique = unique;
    ambt->next = 0;
    addAmbient(mrt, ambt);
    printf("Ambient parsing completed\n");
    return (mrt->qcode);
}
