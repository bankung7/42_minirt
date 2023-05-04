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

    // setup camera
    mrt.cam.orig = (t_vec3){0, 0, 0};
    mrt.cam.fov = tanf(100 * 0.5 * M_PI / 180);

    // ambient
    // mrt.ambt.ratio = 1;
    // mrt.ambt.color = (t_vec3){1.0, 1.0, 1.0};

    // light
    // mrt.lght.orig = (t_vec3){2, 2, 1};
    // mrt.lght.ratio = 0.5;
    // mrt.lght.color = (t_vec3){1.0, 1.0, 1.0};

    // // setup sphere
    // mrt.spr[0].orig = (t_vec3){0.4, 0, -1.5};
    // mrt.spr[0].r = 0.5;
    // mrt.spr[0].color = (t_vec3){0.8, 0.2, 0.2};
    // // setup sphere
    // mrt.spr[1].orig = (t_vec3){-0.3, 0, -0.7};
    // mrt.spr[1].r = 0.3;
    // mrt.spr[1].color = (t_vec3){0.2, 0.8, 0.2};
    // // setup sphere
    // mrt.spr[2].orig = (t_vec3){0.1, 0.3, -0.5};
    // mrt.spr[2].r = 0.2;
    // mrt.spr[2].color = (t_vec3){0.2, 0.2, 0.8};
    
    // // setup back plane
    // mrt.pl[0].p = (t_vec3){0, 0, -5};
    // mrt.pl[0].normal = (t_vec3){0, 0, 1};
    // mrt.pl[0].color = ft_randomColor();
    // // setup right plane
    // mrt.pl[1].p = (t_vec3){4, 0, -5};
    // mrt.pl[1].normal = (t_vec3){-1, 0, 0};
    // mrt.pl[1].color = ft_randomColor();
    // // setup left plane
    // mrt.pl[2].p = (t_vec3){-4, 0, -5};
    // mrt.pl[2].normal = (t_vec3){1, 0, 0};
    // mrt.pl[2].color = ft_randomColor();
    // // setup lower plane
    // mrt.pl[3].p = (t_vec3){0, -1.5, -5};
    // mrt.pl[3].normal = (t_vec3){0, 1, 0};
    // mrt.pl[3].color = ft_randomColor();
    // // setup upper plane
    // mrt.pl[4].p = (t_vec3){0, 4, -5};
    // mrt.pl[4].normal = (t_vec3){0, -1, 0};
    // mrt.pl[4].color = (t_vec3){1, 1, 1};

    ft_render(&mrt);

    // try close window
    mlx_destroy_image(mrt.mlx.mlx, mrt.mlx.img);
    mlx_destroy_window(mrt.mlx.mlx, mrt.mlx.mlx_win);

    ft_clean(&mrt);
    return (0);
}