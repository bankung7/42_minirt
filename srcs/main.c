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

    // setup camera
    mrt.cam.o = (t_vec3){0, 0, 0};
    mrt.cam.fov = tanf(90 * 0.5 * M_PI / 180);

    // setup sphere
    mrt.spr[0].orig = (t_vec3){0.5, 0, -1};
    mrt.spr[0].r = 0.4;
    mrt.spr[0].color = (t_vec3){255, 0 ,0};
    // setup sphere
    mrt.spr[1].orig = (t_vec3){-1, 0, -2};
    mrt.spr[1].r = 0.7;
    mrt.spr[1].color = (t_vec3){0, 230 ,20};
    
    // setup plane
    mrt.pl[0].p = (t_vec3){0, -1, -5};
    mrt.pl[0].normal = (t_vec3){0, 0, 1};
    mrt.pl[0].color = (t_vec3){0, 0, 230};

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