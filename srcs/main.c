#include "minirt.h"

int main(void)
{
    // declare
    t_mrt mrt;
    mrt.cam.ratio = 16.0 / 9.0;
    mrt.width = 800;
    mrt.height = (int)(mrt.width / mrt.cam.ratio);
    mrt.spp = 100;

    // camera
    double vh = 2;
    double vw = mrt.cam.ratio * vh;
    double flen = 1.0;
    mrt.cam.o = (t_vec3){0, 0, 0};
    t_vec3 hoz = (t_vec3){vw, 0, 0};
    t_vec3 vet = (t_vec3){0, vh, 0};
    t_vec3 llc = (t_vec3){
        mrt.cam.o.x - hoz.x / 2 - vet.x / 2 - 0,
        mrt.cam.o.y - hoz.y / 2 - vet.y / 2 - 0,
        mrt.cam.o.z - hoz.z / 2 - vet.z / 2 - flen};

    // sphere 1
    mrt.sphere[0].o = (t_vec3){0, 0, -1};
    mrt.sphere[0].r = 0.5;
    mrt.sphere[0].c = (t_vec3){1.0, 0, 0};
    // sphere 2
    mrt.sphere[1].o = (t_vec3){0, -100.5, -1};
    mrt.sphere[1].r = 100;
    mrt.sphere[1].c = (t_vec3){0, 0.6, 0.2};

    srand(1);
    ft_setupMLX(&mrt);

    // render
    for (int j = mrt.height - 1; j >= 0; --j)
    {
        for (int i = 0; i < mrt.width; ++i)
        {
            // Antilias
            t_vec3 color = (t_vec3){0, 0, 0};
            for (int s = 0; s < mrt.spp; ++s)
            {
                double u = (i + ft_randDouble()) / (mrt.width - 1);
                double v = (j + ft_randDouble()) / (mrt.height - 1);
                t_ray r = ft_makeRay(&mrt, ft_vec3Plus(ft_vec3Mul(hoz, u), ft_vec3Mul(vet, v)), llc);
                color = ft_vec3Plus(color, ft_rayColor(&mrt, &r));
            }
            ft_putPixel(&mrt.mlx, i, mrt.height - j - 1, ft_vec3ToColor(color));
            // // printf("%.2f, %.2f, %.2f\n", color.x, color.y, color.z);
            // printf("%d\n", ft_vec3ToColor(color));

            // double u = (i + 0.0) / (mrt.width - 1);
            // double v = (j + 0.0) / (mrt.height - 1);
            // t_ray r = ft_makeRay(&mrt, ft_vec3Plus(ft_vec3Mul(hoz, u), ft_vec3Mul(vet, v)), llc);
            // ft_putPixel(&mrt.mlx, i, mrt.height - j - 1, ft_vec3ToColor(ft_rayColor(&mrt, &r)));
        }
        printf("%d\n", (int)((1 - (double)j / mrt.height) * 100));
        printf("\x1b[1F");
        printf("\x1b[2K");
    }

    // mlx to image
    mlx_put_image_to_window(mrt.mlx.mlx, mrt.mlx.mlx_win, mrt.mlx.img, 0, 0);
    mlx_loop(mrt.mlx.mlx);

    return (0);
}