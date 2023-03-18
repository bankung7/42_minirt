#include "minirt.h"

int ft_setup(t_mrt *mrt)
{
    mrt->mlx = mlx_init();
    mrt->mlx_win = mlx_new_window(mrt->mlx, W_WIDTH, W_WIDTH / CAM_RATIO, "RayTracer");
    mrt->img.img = mlx_new_image(mrt->mlx, W_WIDTH, W_WIDTH / CAM_RATIO);
    mrt->img.addr = mlx_get_data_addr(mrt->img.img, &mrt->img.bpp, &mrt->img.len, &mrt->img.end);
    
    mrt->cam.vpHgt = 2.0;
    mrt->cam.vpWdt = CAM_RATIO * mrt->cam.vpHgt;
    mrt->cam.flen = 1.0;
    mrt->w_hgt = W_WIDTH / CAM_RATIO;

    // get from input later
    mrt->cam.crdt.x = 0;
    mrt->cam.crdt.y = 0;
    mrt->cam.crdt.z = 0;

    // follow the guide
    mrt->cam.hoz.x = mrt->cam.vpHgt;
    mrt->cam.hoz.y = 0;
    mrt->cam.hoz.z = 0;
    mrt->cam.vet.x = 0;
    mrt->cam.vet.y = mrt->cam.vpWdt;
    mrt->cam.vet.z = 0;
    mrt->cam.llc.x = mrt->cam.crdt.x - mrt->cam.hoz.x / 2 - mrt->cam.vet.x / 2;
    mrt->cam.llc.y = mrt->cam.crdt.y - mrt->cam.hoz.y / 2 - mrt->cam.vet.y / 2;
    mrt->cam.llc.z = mrt->cam.crdt.z - mrt->cam.hoz.z / 2 - mrt->cam.vet.z / 2 - mrt->cam.flen;

    return (0);
}