#include "minirt.h"

int	mClose(int keycode, t_mrt *mrt)
{
    if (keycode == 53)
    {
	    mlx_destroy_window(mrt->mlx.mlx, mrt->mlx.mlx_win);
        clean(mrt, 0);
        exit(0);
    }
	return (0);
}

int	mExit(t_mrt *mrt)
{
	mlx_destroy_window(mrt->mlx.mlx, mrt->mlx.mlx_win);
	clean(mrt, 0);
	exit(0);
	return (0);
}
