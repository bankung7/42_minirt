#ifndef MINIRT_H
#define MINIRT_H

# include <stdio.h>
# include <math.h>
# include <limits.h>
# include "mlx.h"
# include "libft.h"
# include "vector.h"

// shape code
#define SPHERE 10
#define PLANE 20
#define CYLINDER 30

#define MRTW 800
#define MRTH 600

// structure
typedef struct s_ambient
{
    double ratio;
    t_vec3 color;
    int unique;
    struct s_ambient *next;
}   t_ambient;

typedef struct s_light
{
    t_vec3 orig;
    double ratio;
    t_vec3 color;
    int unique;
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
    int unique;
    struct s_camera *next;
}   t_camera;

typedef struct s_object
{
    int type;
    t_vec3 orig;
    t_vec3 rot;
    double radius;
    double height;
    t_vec3 color;
    int unique;
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
    t_ambient *ambt;
    t_camera *cam;
    t_light *lght;
    t_object *obj;
    int qcode;
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

// parsing.c
int qCode(t_mrt *mrt, int n);
int parsing(t_mrt *mrt, char *str);

// ambient.c
int getambient(t_mrt *mrt, char **attr, int unique);

// camera.c
int getCamera(t_mrt *mrt, char **attr, int unique);
int camera(t_mrt *mrt);

// light.c
int getlight(t_mrt *mrt, char **attr, int unique);
int shading(t_mrt *mrt, t_rec *rec);

// camera.c
int getCamera(t_mrt *mrt, char **attr, int unique);
int camera(t_mrt *mrt);
int switch_cam(t_mrt *mrt);

// object.c
int addObject(t_mrt *mrt, t_object *node);
int getObject(t_mrt *mrt, char **attr);

// render.c
void putPixel(t_mlx *data, int x, int y, int color);
void setup(t_mrt *mrt);
int render(t_mrt *mrt);

// ray.c
int makeColor(t_vec3 color);
int trace(t_mrt *mrt, int i, int j);
double hitSphere(t_mrt *mrt, t_ray *r, t_object *obj, t_rec *rec);
double hitPlane(t_mrt *mrt, t_ray *r, t_object *obj, t_rec *rec);
double hitCylinder(t_mrt *mrt, t_ray *r, t_object *obj, t_rec *rec);

// log.c
int elog(char *str, int res);
int free2(char **arr);
int clean(t_mrt *mrt, int res);

//freelist.c
int freelist(t_list *list);
int freelista(t_ambient *list);
int freelistc(t_camera *list);
int freelistl(t_light *list);
int freelisto(t_object *list);

// utils.c
t_vec3 getvec3(t_mrt *mrt, char *str, int color);
double getdouble(char *str);
int checkvalue(t_mrt *mrt, double n, double min, double max);
int checkvec3(t_mrt *mrt, t_vec3 v, double min, double max);
int arr_len(char **arr);

// event.c
int m_close(int keycode, t_mrt *mrt);
int	m_exit(t_mrt *mrt);

#endif
