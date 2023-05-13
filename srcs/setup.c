#include "minirt.h"

int ft_setup(t_mrt *mrt)
{
    mrt->lght = 0;
    mrt->obj = 0;
    mrt->cam = 0;
    mrt->scrn.width = 800;
    mrt->scrn.height = 600;
    mrt->scrn.aspectRatio = (double)mrt->scrn.width / mrt->scrn.height;
    ft_setupMLX(mrt);
    return (0);
}