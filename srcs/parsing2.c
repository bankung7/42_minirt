#include "minirt.h"

// get ambient
int getAmbient(t_mrt *mrt, char **attr)
{
    t_ambient *ambt;

    ambt = malloc(sizeof(t_ambient));
    if (!abmt)
        return (qCode(mrt, 1));

    // get ratio
    ambt->ratio = getDouble(attr[1]);
    printf("%.4f\n", ambt->ratio);

    // get color

    return (mrt->qcode);
}