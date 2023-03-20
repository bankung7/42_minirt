#include "minirt.h"

int ft_setup(t_mrt *mrt)
{
    mrt->mlx = mlx_init();
    mrt->mlx_win = mlx_new_window(mrt->mlx, W_WIDTH, W_WIDTH / CAM_RATIO, "RayTracer");
    mrt->img.img = mlx_new_image(mrt->mlx, W_WIDTH, W_WIDTH / CAM_RATIO);
    mrt->img.addr = mlx_get_data_addr(mrt->img.img, &mrt->img.bpp, &mrt->img.len, &mrt->img.end);
    
    // settin cam
    mrt->cam.crdt = (t_vec){0, 0, 0};
    mrt->cam.fov = 70;

    // setting up image
    mrt->w_hgt = W_WIDTH / CAM_RATIO;

    mrt->cam.vpHgt = 2.0;
    mrt->cam.vpWdt = CAM_RATIO * mrt->cam.vpHgt;
    mrt->cam.flen = 1.0;

    mrt->cam.hoz = (t_vec){mrt->cam.vpWdt, 0, 0};
    mrt->cam.vet = (t_vec){0, mrt->cam.vpHgt, 0};
    mrt->cam.llc = ft_vecMinus(mrt->cam.crdt, ft_vecDev(mrt->cam.hoz, 2));
    mrt->cam.llc = ft_vecMinus(mrt->cam.llc, ft_vecDev(mrt->cam.vet, 2));
    mrt->cam.llc = ft_vecMinus(mrt->cam.llc, (t_vec){0, 0, mrt->cam.flen});

    // ft_info(mrt->cam.crdt);printf("\n");
    // ft_info(mrt->cam.hoz);printf("\n");
    // ft_info(mrt->cam.vet);printf("\n");
    // ft_info(mrt->cam.llc);


    return (0);
}