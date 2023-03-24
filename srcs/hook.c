#include "minirt.h"

int	ft_keyhook(int keycode, t_mrt *mrt)
{
    if (keycode == 125 && mrt->cam.fov > 0)
        mrt->cam.fov--;
    else if (keycode == 126 && mrt->cam.fov < 180)
        mrt->cam.fov++;
    else if (keycode == 53)
        return (ft_close(mrt));
    else
        return (0);
    ft_recal(mrt);
    // printf("%d\n", mrt->cam.fov);
    ft_render(mrt);
	return (0);
}

int ft_close(t_mrt *mrt)
{
    mlx_destroy_image(mrt->mlx, mrt->img.img);
    mlx_destroy_window(mrt->mlx, mrt->mlx_win);
    printf("Nice to see you\n");
    exit(0);
}