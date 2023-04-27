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

// ray
typedef struct s_ray
{
    t_vec3 o;
    t_vec3 dir;
}   t_ray;

// record
typedef struct s_rec
{
    t_vec3 p;
    t_vec3 normal;
    double t;
    t_ray ray;
    int hit;
    t_vec3 c;
}   t_rec;

// camera
typedef struct s_cam
{
    t_vec3 o;
    int fov;
    double ratio;
}   t_cam;

// sphere
typedef struct s_sphere
{
    t_vec3 o;
    double r;
    t_vec3 c;
    struct s_sphere *next;
}   t_sphere;

// minirt data
typedef struct s_mrt
{
    t_mlx mlx;
    int width;
    int height;
    t_cam cam;
    t_sphere sphere[3];
}   t_mrt;

// mlx.c
void ft_putPixel(t_mlx *data, int x, int y, int color);
void ft_setupMLX(t_mrt *mrt);

// ray.c
t_vec3 ft_rayAt(t_ray *r, double t);
t_vec3 ft_rayColor(t_mrt *mrt, t_ray *r);
t_ray ft_makeRay(t_mrt *mrt, t_vec3 w, t_vec3 llc);

// hits.c
int ft_hitSphere(t_sphere *spr, t_rec *rec, double tmin, double tmax);
int ft_worldHit(t_mrt *mrt, t_rec *rec, double tmin, double tmax);

// utils.c
double ft_randDouble(void);
double ft_randDoubleRange(double min, double max);
int ft_vec3ToColor(t_vec3 v);

#endif
