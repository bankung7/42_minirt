#include "minirt.h"

#ifndef WIN_WIDTH
# define WIN_WIDTH 800
#endif

#ifndef WIN_HEIGHT
# define WIN_HEIGHT 600
#endif

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
    t_vector crdt;
    t_vector rot;
    int fov;
} t_cam;

typedef struct s_lght
{
    t_vector crdt;
    double brght;
    t_color color;
} t_lght;

typedef struct s_sphere
{
    t_vector crdt;
    double dmt;
    t_color color;
} t_sphere;

typedef struct s_cynd
{
    t_vector crdt;
    t_vector rot;
    t_color color;
} t_cynd;

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
    t_ambt ambt;
    t_cam cam;
    t_lght lght;
}   t_mrt;