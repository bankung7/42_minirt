#include "minirt.h"

void putPixel(t_mlx *data, int x, int y, int color)
{
    char *dst;

    dst = data->addr + (y * data->llen + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}

void setup(t_mrt *mrt)
{
    mrt->width = 800;
    mrt->height = 600;
    mrt->aspectRatio = (double)mrt->width / mrt->height;

    mrt->mlx.mlx = mlx_init();
    mrt->mlx.mlx_win = mlx_new_window(mrt->mlx.mlx, mrt->width,
        mrt->height, "My minirt");
    mrt->mlx.img = mlx_new_image(mrt->mlx.mlx, mrt->width,
        mrt->height);
    mrt->mlx.addr = mlx_get_data_addr(mrt->mlx.img, &mrt->mlx.bpp,
        &mrt->mlx.llen, &mrt->mlx.endian);
}

int render(t_mrt *mrt)
{
    for (int j = 0; j < mrt->height; ++j)
    {
        for (int i = 0; i < mrt->width; ++i)
        {
            putPixel(&mrt->mlx, i, j, trace(mrt, i, j));
        }
    }
    printf("rendering completed\n");
    mlx_put_image_to_window(mrt->mlx.mlx, mrt->mlx.mlx_win, mrt->mlx.img, 0, 0);
    mlx_hook(mrt->mlx.mlx_win, 2, 1L<<0, mClose, mrt);
    mlx_loop(mrt->mlx.mlx);
    return (0);
}
