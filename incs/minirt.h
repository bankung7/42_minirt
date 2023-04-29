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

// record
typedef struct s_rec
{
    double t1;
    double t2;
    t_vec3 phit;
    t_vec3 normal;
    int hit;
    t_vec3 color;
}   t_rec;

// ray
typedef struct s_ray
{
    t_vec3 orig;
    t_vec3 dir;
}   t_ray;

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

typedef struct s_sphere
{
    t_vec3 orig;
    double r;
    t_vec3 color;
}   t_sphere;

typedef struct s_plane
{
    t_vec3 p;
    t_vec3 normal;
    t_vec3 color;
}   t_plane;

// minirt data
typedef struct s_mrt
{
    t_mlx mlx;
    t_screen scrn;
    t_cam cam;
    t_sphere spr[2];
    t_plane pl[5];
}   t_mrt;

// mlx.c
void ft_putPixel(t_mlx *data, int x, int y, int color);
void ft_setupMLX(t_mrt *mrt);

// utils.c
int ft_vec3ToInt(t_vec3 v);
t_vec3 ft_pixelToSpace(t_mrt *mrt, int i, int j);
t_vec3 ft_randomColor(void);

// hit.c
double ft_hitSphere(t_sphere *spr, t_ray *r, double tmin, double tmax);
double ft_hitPlane(t_plane *plane, t_ray *r);

// ray.c
void ft_rayInfo(t_ray r);
int ft_rayColor(t_mrt *mrt, t_ray *r);
t_ray ft_makeRay(t_mrt *mrt, t_vec3 vec);

#endif
