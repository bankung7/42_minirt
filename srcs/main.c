#include "minirt.h"

int main(int argc, char **argv)
{
    t_mrt mrt;
    
    // parsing
    if (argc != 2)
        return (ft_log("Error\nUsage: ./minirt [file]", 0));

    mrt.lght = 0;
    mrt.obj = 0;
    mrt.cam = 0;

    if (ft_parsing(&mrt, argv[1]))
        return (1);
    
    // setup screen
    mrt.scrn.width = 1280;
    mrt.scrn.height = 968;
    mrt.scrn.aspectRatio = (double)mrt.scrn.width / mrt.scrn.height;

    // setup mlx
    ft_setupMLX(&mrt);
    ft_parameter(&mrt);

    ft_render(&mrt);

    return (0);
}
