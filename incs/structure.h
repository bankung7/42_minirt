#include "minirt.h"

typedef struct s_color
{
    int r;
    int g;
    int b;
} t_color;

typedef struct s_ambt
{
    double ratio;
    t_color color;
} t_ambt;

typedef struct s_cam
{
    t_vec crdt;
    t_vec rot;
    int fov;
    double vpHgt;
    double vpWdt;
    double flen;
    t_vec hoz;
    t_vec vet;
    t_vec llc;
} t_cam;

typedef struct s_light
{
    t_vec crdt;
    double brght;
    t_color color;
    struct s_light *next;
} t_light;

typedef struct s_plane
{
    t_vec crdt;
    t_vec rot;
    t_color color;
    struct s_plane *next;
} t_plane;

typedef struct s_sphere
{
    t_vec crdt;
    double dmt;
    t_color color;
    struct s_sphere *next;
} t_sphere;

typedef struct s_cynd
{
    t_vec crdt;
    t_vec rot;
    double dmt;
    double hgt;
    t_color color;
    struct s_cynd *next;
} t_cynd;

typedef struct s_ray
{
    t_vec o;
    t_vec dir;
} t_ray;

typedef struct s_data
{
    void    *img;
    char    *addr;
    int bpp;
    int len;
    int end;
}   t_data;

typedef struct s_mrt
{
    void *mlx;
    void *mlx_win;
    t_data img;
    t_ambt *ambt;
    t_cam *cam;
    t_light *light;
    t_plane *plane;
    t_sphere *sphere;
    t_cynd *cylinder;
    int status;
}   t_mrt;