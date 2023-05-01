#include "minirt.h"

// Basic algorithm
// 1 Place the camera and the viewport
// 2 For each pixel on the canvas
//  2.1 determine which the square on the view port corresponds to pixel
//  2.2 determine color seen through that square
//  2.3 paint the pixel with that color

int main(void)
{
    t_mrt mrt;
    
    // setup screen
    mrt.scrn.width = 640;
    mrt.scrn.height = 480;
    mrt.scrn.aspectRatio = (double)mrt.scrn.width / mrt.scrn.height;
    
    // setup mlx
    ft_setupMLX(&mrt);

    // srand
    srand(0);

    // setup camera
    mrt.cam.o = (t_vec3){0, 0, 0};
    mrt.cam.fov = tanf(90 * 0.5 * M_PI / 180);

    // ambient
    mrt.ambt.ratio = 1;
    mrt.ambt.color = ft_vec3Mul((t_vec3){1.0, 1.0, 1.0}, mrt.ambt.ratio);

    // light
    mrt.lght.orig = (t_vec3){1, 1, 0};
    mrt.lght.ratio = 1.0;
    mrt.lght.color = (t_vec3){1.0, 1.0, 1.0};

    // setup sphere
    mrt.spr[0].orig = (t_vec3){0.6, 0, -1.5};
    mrt.spr[0].r = 0.5;
    mrt.spr[0].color = (t_vec3){0.8, 0.2, 0.2};
    // setup sphere
    mrt.spr[1].orig = (t_vec3){-0.6, 0, -1.5};
    mrt.spr[1].r = 0.5;
    mrt.spr[1].color = (t_vec3){0.2, 0.8, 0.2};
    
    // // setup plane
    // mrt.pl[0].p = (t_vec3){0, 0, -5};
    // mrt.pl[0].normal = (t_vec3){0, 0, 1};
    // mrt.pl[0].color = ft_randomColor();
    // // setup plane
    // mrt.pl[1].p = (t_vec3){4, 0, -5};
    // mrt.pl[1].normal = (t_vec3){1, 0, 0};
    // mrt.pl[1].color = ft_randomColor();
    // // setup plane
    // mrt.pl[2].p = (t_vec3){-4, 0, -5};
    // mrt.pl[2].normal = (t_vec3){1, 0, 0};
    // mrt.pl[2].color = ft_randomColor();
    // // setup plane
    // mrt.pl[3].p = (t_vec3){0, -4, -5};
    // mrt.pl[3].normal = (t_vec3){0, 1, 0};
    // mrt.pl[3].color = ft_randomColor();
    // // setup plane
    // mrt.pl[4].p = (t_vec3){0, 4, -5};
    // mrt.pl[4].normal = (t_vec3){0, 1, 0};
    // mrt.pl[4].color = ft_randomColor();

    // render
    for (int j = 0; j < mrt.scrn.height; ++j)
    {
        for (int i = 0; i < mrt.scrn.width; ++i)
        {
            // create ray
            t_vec3 vec = ft_pixelToSpace(&mrt, i, j);
            t_ray ray = ft_makeRay(&mrt, vec);
            // ft_rayInfo(ray);
            ft_putPixel(&mrt.mlx, i, j, ft_rayColor(&mrt, &ray));
        }
    }
    mlx_put_image_to_window(mrt.mlx.mlx, mrt.mlx.mlx_win, mrt.mlx.img, 0, 0);
    mlx_loop(mrt.mlx.mlx);

    return (0);
}