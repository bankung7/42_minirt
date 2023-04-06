#include "minirt.h"

void ft_render(t_mrt *mrt)
{
    for (int j = W_HEIGHT - 1; j >= 0; --j)
    {
        for (int i = 0; i < W_WIDTH; ++i)
        {
            double v = (double)j / W_HEIGHT;
            double u = (double)i / W_WIDTH;
            t_ray r = ft_createRay(*mrt->cam, u, v);
            ft_mlx_put_pixel(&mrt->img, i, j, ft_rayColor(mrt, r));
        }
    }
    mlx_put_image_to_window(mrt->mlx, mrt->mlx_win, mrt->img.img, 0, 0);
}
