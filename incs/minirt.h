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
    t_vec3 p;
    t_vec3 normal;
    double t;
    t_vec3 c;
    int front;
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

// camera
typedef struct s_cam
{
    t_vec3 o;
    double fov;
}   t_cam;

// sphere
typedef struct s_sphere
{
    t_vec3 o;
    double r;
    t_vec3 color;
    struct s_sphere *next;
}   t_sphere;

// minirt data
typedef struct s_mrt
{
    t_mlx mlx;
    int width;
    int height;
    double aRatio;
    t_cam cam;
    t_sphere sphere[4];
}   t_mrt;

// mlx.c
void ft_putPixel(t_mlx *data, int x, int y, int color);
void ft_setupMLX(t_mrt *mrt);

// ray.c
t_vec3 ft_rayAt(t_ray r, double t);
t_ray ft_makeRay(t_mrt *mrt, t_vec3 llc, t_vec3 hoz, t_vec3 ver);
int ft_rayColor(t_mrt *mrt, t_ray *r);

#endif
