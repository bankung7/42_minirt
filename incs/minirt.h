#ifndef MINIRT_H
#define MINIRT_H

#include <stdio.h>
#include <stdlib.h>

#include "mlx.h"
#include "math.h"
#include "vector.h"

// structure

// ray
typedef struct s_ray
{
    t_vec3 o;
    t_vec3 dir;
}   t_ray;

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

// minirt data
typedef struct s_mrt
{
    t_mlx mlx;
    int width;
    int height;
}   t_mrt;

// mlx.c
void ft_putPixel(t_mlx *data, int x, int y, int color);
void ft_setupMLX(t_mrt *mrt);

#endif
