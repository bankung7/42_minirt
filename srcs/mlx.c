#include "minirt.h"

void ft_putPixel(t_mlx *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->llen + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

void ft_setupMLX(t_mrt *mrt)
{
    mrt->mlx.mlx = mlx_init();
    mrt->mlx.mlx_win = mlx_new_window(mrt->mlx.mlx, mrt->scrn.width,
        mrt->scrn.height, "My minirt");
    mrt->mlx.img = mlx_new_image(mrt->mlx.mlx, mrt->scrn.width,
        mrt->scrn.height);
    mrt->mlx.addr = mlx_get_data_addr(mrt->mlx.img, &mrt->mlx.bpp,
        &mrt->mlx.llen, &mrt->mlx.endian);
}