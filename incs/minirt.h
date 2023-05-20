#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <math.h>
# include <limits.h>
# include "mlx.h"
# include "libft.h"
# include "vector.h"

// structure

typedef struct s_ambient
{
    double ratio;
    t_vec3 color;
}   t_ambient;

typedef struct s_ligth
{
    t_vec3 orig;
    double ratio;
    t_vec3 color;
    struct s_light *next;
}   t_light;

typedef struct s_camera
{
    t_vec3 orig;
    t_vec3 rot;
    double fov;
    t_vec3 u;
    t_vec3 v;
    t_vec3 w;
    double d;
}   t_camera;

typedef struct s_object
{
    int type;
    t_vec3 orig;
    t_vec3 rot;
    double raduis;
    double height;
    t_vec3 color;
    struct s_object *next;
}   t_object;

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

typedef struct s_mrt
{
    t_mlx mlx;
    int width;
    int height;
    double aspectRatio;
    t_ambient ambt;
    t_camera *cam;
    t_light *lght;
    t_object *obj;
}   t_mrt;

typedef struct s_ray
{
    t_vec3 orig;
    t_vec3 dir;
}   t_ray;

typedef struct s_rec
{
    double tnear;
    double tmin;
    double tmax;
    t_vec3 phit;
    t_vec3 normal;
    t_vec3 color;
    int hit;
}   t_rec;

// render.c
void putPixel(t_mlx *data, int x, int y, int color);
void setup(t_mrt *mrt);
int render(t_mrt *mrt);
int makeColor(t_vec3 color);

// shading.c
int shading(t_mrt *mrt, t_rec *rec);

// camera.c
int camera(t_mrt *mrt);

// ray.c
int trace(t_mrt *mrt, int i, int j);

// object.c
int addObject(t_mrt *mrt, t_object *node);
int addLight(t_mrt *mrt, t_light *node);

#endif
