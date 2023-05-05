#include "minirt.h"

// Basic algorithm
// 1 Place the camera and the viewport
// 2 For each pixel on the canvas
//  2.1 determine which the square on the view port corresponds to pixel
//  2.2 determine color seen through that square
//  2.3 paint the pixel with that color

int main(int argc, char **argv)
{
    t_mrt mrt;
    
    // parsing
    if (argc != 2)
        return (ft_log("Error\nUsage: ./minirt [file]", 0));

    mrt.lght = 0;
    mrt.spr = 0;
    mrt.pl = 0;
    mrt.cydn = 0;

    if (ft_parsing(&mrt, argv[1]))
        return (1);
    
    // setup screen
    mrt.scrn.width = 640 * 1.2;
    mrt.scrn.height = 480 * 1.2;
    mrt.scrn.aspectRatio = (double)mrt.scrn.width / mrt.scrn.height;
    
    // setup mlx
    ft_setupMLX(&mrt);
    ft_parameter(&mrt);

    // srand
    srand(0);

    // set fov
    mrt.cam.fov = tanf(mrt.cam.ifov * 0.5 * M_PI / 180);

    ft_render(&mrt);

    return (0);
}
