#include "minirt.h"

// Basic algorithm
// 1 Place the camera and the viewport
// 2 For each pixel on the canvas
//  2.1 determine which the square on the view port corresponds to pixel
//  2.2 determine color seen through that square
//  2.3 paint the pixel with that color

// convert pixel to world coordinate (raster->NDC->world)
t_vec3 ft_pixelToSpace(t_mrt *mrt, int i, int j)
{
    t_vec3 vec;
    vec.x = (2 * ((i + 0.5) / mrt->scrn.width) - 1);
    vec.y = (1 - 2 * ((j + 0.5) / mrt->scrn.height));
    vec.z = -1;
    return (vec);
}

int main(void)
{
    t_mrt mrt;
    

    // setup screen
    mrt.scrn.height = 400;
    mrt.scrn.aspectRatio = 16.0 / 9.0;
    mrt.scrn.width = mrt.scrn.height * mrt.scrn.aspectRatio;
    
    // setup mlx
    ft_setupMLX(&mrt);

    // setup camera
    mrt.cam.o = (t_vec3){0, 0, 0};
    mrt.cam.fov = tanf(22.5 / 2 * M_PI / 180);
    
    // render
    for (int j = 0; j < mrt.scrn.height; ++j)
    {
        for (int i = 0; i < mrt.scrn.width; ++i)
        {
            t_vec3 vec = ft_pixelToSpace(&mrt, i, j);
            printf("%.2f, %.2f, %.2f\n", vec.x, vec.y, vec.z);
        }
    }




    return (0);
}