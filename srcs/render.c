#include "minirt.h"

int ft_setup(t_mrt *mrt)
{
    // setup mlx
    mrt->mlx = mlx_init();
    mrt->mlx_win = mlx_new_window(mrt->mlx, W_WIDTH, W_HEIGHT, "RayTracer");
    mrt->img.img = mlx_new_image(mrt->mlx, W_WIDTH, W_HEIGHT);
    mrt->img.addr = mlx_get_data_addr(mrt->img.img, &mrt->img.bpp, &mrt->img.len, &mrt->img.end);
    
    // settin cam
    mrt->cam->crdt = (t_vec){0, 0, 0};
    mrt->cam->fov = 70;

    // setup viewport
    mrt->cam->vpHgt = 2.0;
    mrt->cam->vpWdt = CAM_RATIO * mrt->cam->vpHgt;

    mrt->cam->hoz = (t_vec){mrt->cam->vpWdt, 0, 0};
    mrt->cam->vet = (t_vec){0, mrt->cam->vpHgt, 0};
    // printf("%f\n", mrt->cam->flen);
    ft_recal(mrt);

    return (0);
}

// recal
int ft_recal(t_mrt *mrt)
{
    mrt->cam->flen = (mrt->cam->vpWdt / 2) * tan(mrt->cam->fov * M_PI / 360);
    mrt->cam->hoz = (t_vec){mrt->cam->vpWdt, 0, 0};
    mrt->cam->vet = (t_vec){0, mrt->cam->vpHgt, 0};
    mrt->cam->llc = ft_vecMinus(mrt->cam->crdt, ft_vecDev(mrt->cam->hoz, 2));
    mrt->cam->llc = ft_vecMinus(mrt->cam->llc, ft_vecDev(mrt->cam->vet, 2));
    mrt->cam->llc = ft_vecMinus(mrt->cam->llc, (t_vec){0, 0, mrt->cam->flen});
    return (0);
}

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
