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
    while (line)
    {
        ft_checkline(line, mrt);
        free(line);
        line = 0;
    }

    return (0);
}

int ft_checkline(char *line, t_mrt *mrt)
{
    (void)mrt;
    printf("line : %s\n", line);
    while (line)
    {
        if (ft_isalnum(*line) && (*line == 'A'))
            return (ft_getAmbt(line, mrt));
        line++;
    }
    return (0);
}

// Ambient lightning:
// A 0.2 255,255,255
// [iden] [ratio] [colorRGB]
// identifier: A
// ambient lighting ratio in range [0.0,1.0]: 0.2
// R,G,B colors in range [0-255]: 255, 255, 255
int ft_getAmbt(char *line, t_mrt *mrt)
{
    (void)line;
    (void)mrt;
    printf("get ambient arg\n");
    char **attr = ft_split(line, ' ');
    ft_parr(attr);
    mrt->ambt.ratio = ft_atoi(attr[1]);
    char **attr1 = ft_split(attr[2], ',');
    mrt->ambt.color.r = ft_atoi(attr1[0]);
    mrt->ambt.color.g = ft_atoi(attr1[1]);
    mrt->ambt.color.b = ft_atoi(attr1[2]);
    ft_free2(attr1);
    ft_free2(attr);

    printf("ratio: %f\n", mrt->ambt.ratio);
    printf("color: %d %d %d\n", mrt->ambt.color.r, mrt->ambt.color.g, mrt->ambt.color.b);
    return (0);
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
