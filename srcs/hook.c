#include "minirt.h"

int	ft_hook(int keycode, t_mrt *mrt)
{
    if (keycode == 123)
        mrt->lght.orig.x -= 0.1;
    else if (keycode == 124)
        mrt->lght.orig.x += 0.1;
    printf("input key : %d\n", keycode);
    ft_render(mrt);
	return (0);
}