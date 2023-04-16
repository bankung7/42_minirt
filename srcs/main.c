#include "minirt.h"

int main(void)
{
    t_mrt mrt;
    mrt.width = 400;
    mrt.height = 400;
    double fov = 30;
    double aspect_ratio = mrt.width / (double)mrt.height;
    double angle = tanf(M_PI * 0.5 * fov / 180.0);

    ft_setupMLX(&mrt);

    for (int y = 0; y < mrt.height; ++y)
    {
        for (int x = 0; x < mrt.width; ++x)
        {
            double xx = (2 * ((x + 0.5) * (1.0 / mrt.width)) - 1) * angle * aspect_ratio;
            double yy = (1 - 2 * ((y + 0.5) * (1.0 / mrt.height))) * angle;
            printf("%.2f, %.2f\n", xx, yy);
            ft_putPixel(&mrt.mlx, x, mrt.height - y - 1, 0xFFFFFF);
        }
    }

    mlx_put_image_to_window(mrt.mlx.mlx, mrt.mlx.mlx_win, mrt.mlx.img, 0, 0);
    mlx_loop(mrt.mlx.mlx);
    return (0);
}