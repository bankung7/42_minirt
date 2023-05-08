#include "minirt.h"

int main(int argc, char **argv)
{
    t_mrt mrt;
    
    // parsing
    if (argc != 2)
        return (ft_log("Error\nUsage: ./minirt [file]", 0));

    mrt.lght = 0;
    mrt.obj = 0;

    if (ft_parsing(&mrt, argv[1]))
        return (1);
    
    // setup screen
    mrt.scrn.width = 640 * 1.2;
    mrt.scrn.height = 480 * 1.2;
    mrt.scrn.aspectRatio = (double)mrt.scrn.width / mrt.scrn.height;

    // set fov
    mrt.cam.fov = tan(mrt.cam.ifov * 0.5 * M_PI / 180);

    // setup basic vector
    mrt.cam.w = ft_vec3Unit(ft_vec3Minus(mrt.cam.orig, (t_vec3){0, 0, -1}));
    mrt.cam.u = ft_vec3Unit(ft_vec3Cross(mrt.cam.rot, mrt.cam.w));
    mrt.cam.v = ft_vec3Cross(mrt.cam.w, mrt.cam.u);
    
    // setup mlx
    ft_setupMLX(&mrt);
    ft_parameter(&mrt);

    ft_render(&mrt);

    return (0);
}
