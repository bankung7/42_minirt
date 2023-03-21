#include "minirt.h"

// Parsing for file .rt
int ft_parsing(t_mrt *mrt, char *file)
{
    int fd;
    (void)mrt;

    // check file extension
    if (ft_strlen(file) < 4 || ft_strncmp(&file[ft_strlen(file) - 3], ".rt", 3)
        || ft_strlen(file) - (ft_strchr(file, '.') - file) != 3)
    {
        printf("minirt: error: file name incorrect\n");
        return (1);
    }

    fd = open(file, O_RDONLY);
    if (fd == -1)
    {
        perror("minirt: error: ");
        return (1);
    }

    char *line;
    line = get_next_line(fd);
    if (!line)
        return (1);
    while (line)
    {
        ft_checkline(line, mrt);
        free(line);
        line = get_next_line(fd);
    }
    return (0);
}

int ft_checkline(char *line, t_mrt *mrt)
{
    char **arr = ft_split(line, ' ');
    // ft_parr(arr);
    
    if (!ft_strncmp(arr[0], "A", 2))
        ft_getAmbient(arr, mrt);
    ft_free2(arr);

    return (0);
}


// Ambient lightning:
// A 0.2 255,255,255
// [iden] [ratio] [colorRGB]
// identifier: A
// ambient lighting ratio in range [0.0,1.0]: 0.2
// R,G,B colors in range [0-255]: 255, 255, 255
int ft_getAmbient(char **arr, t_mrt *mrt)
{
    (void)mrt;
    printf("this is Ambient value\n");
    // ft_parr(arr);
    char **ratio = ft_getAttr(arr[1], 1);
    char **color = ft_getAttr(arr[2], 3);

    mrt->ambt.ratio = ft_atof(ratio[0]);
    mrt->ambt.color.r = ft_atoi(color[0]);
    mrt->ambt.color.g = ft_atoi(color[1]);
    mrt->ambt.color.b = ft_atoi(color[2]);

    printf("ratio : %0.1f\n", mrt->ambt.ratio);
    printf("color : [%d][%d][%d]\n", mrt->ambt.color.r, mrt->ambt.color.g, mrt->ambt.color.b);

    ft_free2(ratio);
    ft_free2(color);
    return (0);
}

char **ft_getAttr(char *input, int n)
{
    char **attr = ft_split(input, ',');

    if (ft_arrlen(attr) != n)
    {
        printf("attr mismatch\n");
        return (0);
    }
    return (attr);
}


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

// Sphere:
// sp 0.0,0.0,20.6 12.6 10,0,255
// [iden] [coordinate] [diameter] [colorRGB]
// identifier: sp
// x,y,z coordinates of the sphere center: 0.0,0.0,20.6
// the sphere diameter: 12.6
// R,G,B colors in range [0-255]: 10, 0, 255

// Cylinder:
// cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
// [iden] [coordinate] [rotation vector] [colorRGB]
// identifier: cy
// x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
// 3d normalized vector of axis of cylinder. In range [-1,1] for each x,y,z axis:
// 0.0,0.0,1.0
// the cylinder diameter: 14.2
// the cylinder height: 21.42
// R,G,B colors in range [0,255]: 10, 0, 255

