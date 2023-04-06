#include "minirt.h"

// viewport setup
// let design the viewport height is 2 units and
// viewport width is rational to 16:9
int ft_setup(t_mrt *mrt)
{
    // setup mlx
    mrt->mlx = mlx_init();
    mrt->mlx_win = mlx_new_window(mrt->mlx, W_WIDTH, W_HEIGHT, "RayTracer");
    mrt->img.img = mlx_new_image(mrt->mlx, W_WIDTH, W_HEIGHT);
    mrt->img.addr = mlx_get_data_addr(mrt->img.img, &mrt->img.bpp, &mrt->img.len, &mrt->img.end);
    
    // set cam
    // mrt->cam->crdt = (t_vec){0, 0, 0};

    // setup viewport
    mrt->cam->vpHgt = 2.0;
    mrt->cam->vpWdt = CAM_RATIO * mrt->cam->vpHgt;

    ft_recal(mrt);
    return (0);
}

// recal
int ft_recal(t_mrt *mrt)
{
    // set upper left corner
    mrt->cam->hoz = (t_vec){mrt->cam->vpWdt, 0, 0};
    mrt->cam->vet = (t_vec){0, mrt->cam->vpHgt, 0};
    mrt->cam->flen = (mrt->cam->vpWdt / 2) * tan(mrt->cam->fov * M_PI / 360);
    mrt->cam->llc = ft_vecMinus(mrt->cam->crdt, ft_vecDev(mrt->cam->hoz, 2));
    mrt->cam->llc = ft_vecMinus(mrt->cam->llc, ft_vecDev(mrt->cam->vet, 2));
    mrt->cam->llc = ft_vecMinus(mrt->cam->llc, (t_vec){0, 0, mrt->cam->flen});
    return (0);
}

