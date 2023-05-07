#ifndef MINIRT_H
#define MINIRT_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#include "libft.h"
#include "mlx.h"
#include "math.h"
#include "vector.h"

// let limit the size for all dmt here
#ifndef LIMIT_SIZE
#define LIMIT_SIZE 100
#endif

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
    int hit;
    double t;
    t_vec3 phit;
    t_vec3 normal;
    t_vec3 color;
    double tmin;
    double tmax;
    double tnear;
}   t_rec;

// ray
typedef struct s_ray
{
    t_vec3 orig;
    t_vec3 dir;
}   t_ray;

typedef struct s_screen
{
    int width;
    int height;
    double aspectRatio;
}   t_screen;

// ambient
typedef struct s_ambient
{
    double ratio;
    t_vec3 color;
}   t_ambient;

// camera
typedef struct s_cam
{
    t_vec3 orig;
    t_vec3 rot;
    double ifov;
    double fov;
    t_vec3 u;
    t_vec3 v;
    t_vec3 w;
}   t_cam;

// lighting
typedef struct s_light
{
    t_vec3 orig;
    double ratio;
    t_vec3 color;
    struct s_light *next;
}   t_light;

// sphere
typedef struct s_sphere
{
    t_vec3 orig;
    double dmt;
    double r;
    t_vec3 color;
    struct s_sphere *next;
}   t_sphere;

typedef struct s_plane
{
    t_vec3 p;
    t_vec3 normal;
    t_vec3 color;
    struct s_plane *next;
}   t_plane;

// cylinder
typedef struct s_cylinder
{
    t_vec3 orig;
    t_vec3 rot;
    double dmt;
    double r;
    double height;
    t_vec3 color;
    struct s_cylinder *next;
}   t_cylinder;

// minirt data
typedef struct s_mrt
{
    t_mlx mlx;
    t_screen scrn;
    t_ambient ambt;
    t_cam cam;
    t_light *lght;
    t_sphere *spr;
    t_plane *pl;
    t_cylinder *cydn;
}   t_mrt;

// mlx.c
void ft_putPixel(t_mlx *data, int x, int y, int color);
void ft_setupMLX(t_mrt *mrt);

// utils.c
double ft_clamp(double v, double min, double max);
t_vec3 ft_randomColor(void);
int ft_arrLen(char **arr);
void ft_readAttr(char **attr);
void ft_vec3Info(t_vec3 v);
void ft_addSphere(t_sphere **spr, t_sphere *node);
void ft_addPlane(t_plane **pl, t_plane *node);
void ft_addLight(t_light **lght, t_light *node);
void ft_addCylinder(t_cylinder **cydn, t_cylinder *node);

// hit.c
double ft_hitSphere(t_sphere *spr, t_ray *r, t_rec *rec);
double ft_hitPlane(t_plane *plane, t_ray *r, t_rec *rec);

// ray.c
void ft_rayInfo(t_ray r);
t_vec3 ft_lookAt(t_ray *r, double t);
int ft_rayColor(t_mrt *mrt, t_ray *r);
t_ray ft_makeRay(t_mrt *mrt, t_vec3 vec);

// hook.c
int	ft_exit(int keycode, t_mrt *mrt);

// render.c
void ft_render(t_mrt *mrt);
int ft_vec3ToInt(t_vec3 v);
t_vec3 ft_pixelToSpace(t_mrt *mrt, int i, int j);
void ft_parameter(t_mrt *mrt);

// log.c
int ft_log(char *str, int res);
int ft_flog(char *str, int res, char **arr, char *s);

// parsing.c
double ft_getDouble(char *str);
int ft_checkVec3(t_vec3 *vec, double min, double max);
int ft_setVec3(t_vec3 *vec, char *input , double min, double max);
int ft_checkValue(double n, double min, double max);
int ft_checkAttr(t_mrt *mrt, char **attr);
char **ft_getAttr(char *input, int delim, int n);
int ft_parsing(t_mrt *mrt, char *file);

// parsing2.c
int ft_getAmbient(t_mrt *mrt, char **attr);
int ft_getCamera(t_mrt *mrt, char **input);
int ft_getLight(t_mrt *mrt, char **input);
int ft_getSphere(t_mrt *mrt, char **input);
int ft_getPlane(t_mrt *mrt, char **input);
int ft_getCylinder(t_mrt *mrt, char **input);

// free.c
int ft_free2(char **arr);
void ft_freeList(t_list *node);
int ft_clean(t_mrt *mrt);

#endif
