#include "minirt.h"

void ft_render(t_mrt *mrt)
{
    for (int j = 0; j < mrt->scrn.height; ++j)
    {
        for (int i = 0; i < mrt->scrn.width; ++i)
        {
            // create ray
            t_vec3 vec = ft_pixelToSpace(mrt, i, j);
            t_ray ray = ft_makeRay(mrt, vec);
            // ft_rayInfo(ray);
            ft_putPixel(&mrt->mlx, i, j, ft_rayColor(mrt, &ray));
        }
    }
    mlx_put_image_to_window(mrt->mlx.mlx, mrt->mlx.mlx_win, mrt->mlx.img, 0, 0);
    mlx_hook(mrt->mlx.mlx_win, 2, 1L<<1, ft_hook, mrt);
    mlx_loop(mrt->mlx.mlx);

}
