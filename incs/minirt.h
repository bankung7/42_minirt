#ifndef MINIRT_H
#define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "mlx.h"
#include "math.h"
#include "vector.h"

// mlx data
typedef struct s_mlx
{
    void *mlx;
    void *mlx_win;
    void *img;
    char *addr;
    int bpp;
    int llen;
    int endian;
}   t_mlx;

// camera
typedef struct s_cam
{
    t_vec3 o;
    double fov;
}   t_cam;

typedef struct s_screen
{
    int width;
    int height;
    double aspectRatio;
}   t_screen;

// minirt data
typedef struct s_mrt
{
    t_mlx mlx;
    t_screen scrn;
    t_cam cam;
}   t_mrt;

// mlx.c
void ft_putPixel(t_mlx *data, int x, int y, int color);
void ft_setupMLX(t_mrt *mrt);

#endif
