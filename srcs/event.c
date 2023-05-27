#include "minirt.h"

int	mClose(int keycode, t_mrt *mrt)
{
    printf("keycode : %d\n", keycode);
    if (keycode == 53)
    {
	    mlx_destroy_window(mrt->mlx.mlx, mrt->mlx.mlx_win);
        clean(mrt, 0);
        exit(0);
    }
    if (keycode == 8)
        return (switch_cam(mrt));
	return (0);
}
