#include "minirt.h"

int	ft_exit(int keycode, t_mrt *mrt)
{
    if (keycode == 53)
    {
        mlx_destroy_image(mrt->mlx.mlx, mrt->mlx.img);
        mlx_destroy_window(mrt->mlx.mlx, mrt->mlx.mlx_win);
        // ft_clean(mrt);
        exit(0);
    }
	return (0);
}