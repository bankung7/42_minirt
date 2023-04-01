#include "minirt.h"

// Parsing for file .rt
int ft_parsing(t_mrt *mrt, char *file)
{
    int fd;

    mrt->sphere = 0;
    mrt->cynd = 0;
    // open and check the file
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (ft_error("minirt: cannot open the file", 0));

    // start read each line
    while (ft_readline(mrt, get_next_line(fd)) != 1)
        ;
    return (mrt->status);
}

int ft_readline(t_mrt *mrt, char *line)
{
    if (!line)
        return (1);
    char **attr = ft_getAttr(line, 0, ' ');
    free(line);
    if (!attr)
        return (ft_error2("minirt: parsing error", 1, 0, line));
    if (ft_strncmp(attr[0], "sp", 3) == 0 && ft_arrLen(attr) == 4)
        return (ft_getSphere(mrt, attr));
    if (attr)
        ft_free2(attr);
    return (0);
}

int ft_getVector(t_vec *vec, char **attr, double min, double max)
{
    if (!attr)
        return (1);
    vec->x = ft_atod(attr[0]);
    vec->y = ft_atod(attr[1]);
    vec->z = ft_atod(attr[2]);
    ft_free2(attr);
    return (ft_checkVector(vec, min, max));
}

int ft_checkVector(t_vec *vec, double min, double max)
{
    if (vec->x < min || vec->y < min || vec->z < min
        || vec->x > max || vec->y > max || vec->z > max)
        return (1);
    return (0);
}
// Ambient lightning:
// A 0.2 255,255,255
// [iden] [ratio] [colorRGB]
// identifier: A
// ambient lighting ratio in range [0.0,1.0]: 0.2
// R,G,B colors in range [0-255]: 255, 255, 255

// Camera:
// C -50.0,0,20 0,0,1 70
// [iden] [coordinate] [rotation vector] [FOV]
// identifier: C
// x,y,z coordinates of the view point: -50.0,0,20
// 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
// FOV : Horizontal field of view in degrees in range [0,180]: 70

// Light:
// L -40.0,50.0,0.0 0.6 10,0,255
// [iden] [coordinate] [brightness] [colorRGB]
// identifier: L
// x,y,z coordinates of the light point: -40.0,50.0,0.0
// the light brightness ratio in range [0.0,1.0]: 0.6
// (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255

// Plane:
// pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
// [iden] [coordinate] [rotation vector] [colorRGB]
// identifier: pl
// x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
// 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
// R,G,B colors in range [0-255]: 0,0,225
