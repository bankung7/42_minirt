#include "minirt.h"

// Parsing for file .rt
int ft_parsing(t_mrt *mrt, char *file)
{
    int fd;
    char *line;

    // check file extension
    if (ft_strlen(file) < 4 || ft_strncmp(&file[ft_strlen(file) - 3], ".rt", 3)
        || ft_strlen(file) - (ft_strchr(file, '.') - file) != 3)
        return (ft_error("minirt: error: file name incorrect", 1));

    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (ft_error("minirt: error: file cannot open", 1));

    line = get_next_line(fd);
    if (!line)
    {
        close(fd);
        return (ft_error("minirt: error: file is empty", 1));
    }

    // handle when input from file is error
    while (line)
    {
        if (ft_checkline(line, mrt))
        {
            close(fd);
            return (ft_error2(0, 1, 0, line));
        }
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}

// for the capital letter, do later again.
int ft_checkline(char *line, t_mrt *mrt)
{
    char **arr;
    
    arr = ft_split(line, ' ');
    if (!ft_strncmp(arr[0], "A", 2) && ft_getAmbient(arr, mrt))
        return (ft_error2("error: Ambient value error", 1, arr, 0));
    if (!ft_strncmp(arr[0], "C", 2) && ft_getCamera(arr, mrt))
        return (ft_error2("error: Camera value error", 1, arr, 0));
    // when multiple light, plane and other shape, deal later
    if (!ft_strncmp(arr[0], "L", 2) && ft_getLight(arr, mrt))
        return (ft_error2("error: Light value error", 1, arr, 0));
    if (!ft_strncmp(arr[0], "pl", 3) && ft_getPlane(arr, mrt))
        return (ft_error2("error: Plane value error", 1, arr, 0));
    return (ft_free2(arr));
}

// Ambient lightning:
// A 0.2 255,255,255
// [iden] [ratio] [colorRGB]
// identifier: A
// ambient lighting ratio in range [0.0,1.0]: 0.2
// R,G,B colors in range [0-255]: 255, 255, 255
int ft_getAmbient(char **arr, t_mrt *mrt)
{
    printf("====================================\n");
    printf("this is Ambient value\n");

    if (ft_arrlen(arr) != 3)
        return (ft_error2("error: Ambient incomplete", 1, 0, 0));

    if (ft_setFValue(&mrt->ambt.ratio, ft_getAttr(arr[1], 1), 0.0, 1.0)
        || ft_setColor(&mrt->ambt.color, ft_getAttr(arr[2], 3)))
        return (1);

    printf("ratio : %0.1f\n", mrt->ambt.ratio);
    printf("color : [%d][%d][%d]\n", mrt->ambt.color.r, mrt->ambt.color.g, mrt->ambt.color.b);

    return (0);
}

// Camera:
// C -50.0,0,20 0,0,1 70
// [iden] [coordinate] [rotation vector] [FOV]
// identifier: C
// x,y,z coordinates of the view point: -50.0,0,20
// 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
// FOV : Horizontal field of view in degrees in range [0,180]: 70
int ft_getCamera(char **arr, t_mrt *mrt)
{
    printf("====================================\n");
    printf("This is Camera value\n");
    if (ft_arrlen(arr) != 4)
        return (1);
    
    if (ft_setVector(&mrt->cam.crdt, ft_getAttr(arr[1], 3), -100, 100)
        || ft_setVector(&mrt->cam.rot, ft_getAttr(arr[2], 3), -1.0, 1.0)
        || ft_setIValue(&mrt->cam.fov, ft_getAttr(arr[3], 1), 0, 180))
        return (1);
    
    printf("crdt : [%.1f][%.1f][%.1f]\n", mrt->cam.crdt.x, mrt->cam.crdt.y, mrt->cam.crdt.z);
    printf("rot : [%.1f][%.1f][%.1f]\n", mrt->cam.rot.x, mrt->cam.rot.y, mrt->cam.rot.z);
    printf("fov : %d\n", mrt->cam.fov);
    
    return (0);
}

// Light:
// L -40.0,50.0,0.0 0.6 10,0,255
// [iden] [coordinate] [brightness] [colorRGB]
// identifier: L
// x,y,z coordinates of the light point: -40.0,50.0,0.0
// the light brightness ratio in range [0.0,1.0]: 0.6
// (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255
int ft_getLight(char **arr, t_mrt *mrt)
{
    printf("====================================\n");
    printf("This is Light value\n");
    if (ft_arrlen(arr) != 4)
        return (1);
    
    if (ft_setVector(&mrt->lght.crdt, ft_getAttr(arr[1], 3), -100, 100)
        || ft_setFValue(&mrt->lght.brght, ft_getAttr(arr[2], 1), 0.0, 1.0)
        || ft_setColor(&mrt->lght.color, ft_getAttr(arr[3], 3)))
        return (1);

    printf("crdt : [%.1f][%.1f][%.1f]\n", mrt->lght.crdt.x, mrt->lght.crdt.y, mrt->lght.crdt.z);
    printf("brightness : %.1f\n", mrt->lght.brght);
    printf("color : [%d][%d][%d]\n", mrt->lght.color.r, mrt->lght.color.g, mrt->lght.color.b);
    mrt->lght.next = 0;
    return (0);
}

// Plane:
// pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
// [iden] [coordinate] [rotation vector] [colorRGB]
// identifier: pl
// x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
// 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
// R,G,B colors in range [0-255]: 0,0,225
int ft_getPlane(char **arr, t_mrt *mrt)
{
    printf("====================================\n");
    printf("This is Plane value\n");
    if (ft_arrlen(arr) != 4)
        return (1);
    
    if (ft_setVector(&mrt->plane.crdt, ft_getAttr(arr[1], 3), -100, 100)
        || ft_setVector(&mrt->plane.rot, ft_getAttr(arr[2], 3), -1.0, 1.0)
        || ft_setColor(&mrt->plane.color, ft_getAttr(arr[3], 3)))
        return (1);

    printf("crdt : [%.1f][%.1f][%.1f]\n", mrt->plane.crdt.x, mrt->plane.crdt.y, mrt->plane.crdt.z);
    printf("rot : [%.1f][%.1f][%.1f]\n", mrt->plane.rot.x, mrt->plane.rot.y, mrt->plane.rot.z);
    printf("color : [%d][%d][%d]\n", mrt->plane.color.r, mrt->plane.color.g, mrt->plane.color.b);

    return (0);
}

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

