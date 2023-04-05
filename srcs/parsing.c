#include "minirt.h"

// Parsing for file .rt
int ft_parsing(t_mrt *mrt, char *file)
{
    // check file name
    if (ft_strlen(file) <= 3)
        return (ft_error("minirt: file name incorrect", 1));
    if (ft_strlen(ft_strrchr(file, '.')) != 3)
        return (ft_error("minirt: file extension is not .rt", 1));
    
    // open the file
    int fd;
    fd = open(file, O_RDONLY);
    if (fd == -1)
        return (ft_error("minirt: cannot open the file", 1));

    char *line;
    line = get_next_line(fd);
    while (line)
    {
        if (ft_readline(mrt, line))
            return (ft_error2("minirt: readline error", 1, 0, line));
        free(line);
        line = get_next_line(fd);
    }
    printf("file is open and closed\n");
    close(fd);
    return (0);
}

int ft_readline(t_mrt *mrt, char *line)
{
    char **attr;

    attr = ft_getAttr(line, -1, ' ');
    if (!attr)
        return (ft_error("minirt: parsing error", 1));
    if (ft_strncmp(attr[0], "A", 2) == 0 && ft_arrLen(attr) == 3)
        return (ft_getAmbient(mrt, attr));
    if (ft_strncmp(attr[0], "C", 2) == 0 && ft_arrLen(attr) == 4)
        return (ft_getCamera(mrt, attr));
    if ((ft_strncmp(attr[0], "L", 2) == 0 || ft_strncmp(attr[0], "l", 2) == 0)
        && ft_arrLen(attr) == 4)
        return (ft_getLight(mrt, attr));
    if ((ft_strncmp(attr[0], "PL", 3) == 0 || ft_strncmp(attr[0], "pl", 3) == 0)
        && ft_arrLen(attr) == 4)
        return (ft_getPlane(mrt, attr));
    if ((ft_strncmp(attr[0], "SP", 3) == 0 || ft_strncmp(attr[0], "sp", 3) == 0)
        && ft_arrLen(attr) == 4)
        return (ft_getSphere(mrt, attr));
    if ((ft_strncmp(attr[0], "CY", 3) == 0 || ft_strncmp(attr[0], "cy", 3) == 0)
         && ft_arrLen(attr) == 6)
        return (ft_getCylinder(mrt, attr));
    ft_free2(attr);
    return (0);
}
////////////// check value with out of bound ///////////////

// Ambient lightning:
// A 0.2 255,255,255
// [iden] [ratio] [colorRGB]
// identifier: A
// ambient lighting ratio in range [0.0,1.0]: 0.2
// R,G,B colors in range [0-255]: 255, 255, 255
int ft_getAmbient(t_mrt *mrt, char **attr)
{
    if (mrt->ambt)
        return (ft_error2("minirt: ambient duplicated", 1, attr, 0));
    mrt->ambt = malloc(sizeof(t_ambt));
    if (!mrt->ambt)
        return (ft_error2("minirt: parsing ambient error", 1, attr, 0));
    mrt->ambt->ratio = ft_atod(attr[1]);
    if (ft_getColor(&mrt->ambt->color, ft_getAttr(attr[2], 3, ',')))
        return (ft_error2("minirt: parsing ambient error", 1, attr, 0));
    if (ft_checkValueD(mrt->ambt->ratio, 0, 1) || ft_checkColor(mrt->ambt->color))
        return (ft_error2("minirt: ambient value out of bound", 1, attr, 0));
    ft_free2(attr);
    return (0);
}

// Camera:
// C -50.0,0,20 0,0,1 70
// [iden] [coordinate] [rotation vector] [FOV]
// identifier: C
// x,y,z coordinates of the view point: -50.0,0,20
// 3d normalized orientation vector. In range [-1,1] for each x,y,z axis: 0.0,0.0,1.0
// FOV : Horizontal field of view in degrees in range [0,180]: 70
int ft_getCamera(t_mrt *mrt, char **attr)
{
    if (mrt->cam)
        return (ft_error2("minirt: camera duplicated", 1, attr, 0));
    mrt->cam = malloc(sizeof(t_cam));
    if (!mrt->cam)
        return (ft_error2("minirt: parsing error camera", 1, attr, 0));
    if (ft_getVector(&mrt->cam->crdt, ft_getAttr(attr[1], 3, ',')))
        return (ft_error2("minirt: parsing camera coordinate error", 1, attr, 0));
    if (ft_getVector(&mrt->cam->rot, ft_getAttr(attr[2], 3, ',')))
        return (ft_error2("minirt: parsing camera rotation error", 1, attr, 0));
    mrt->cam->fov = ft_atoi(attr[3]);
    if (ft_checkVector(mrt->cam->rot, -1, 1) || ft_checkValueI(mrt->cam->fov, 0, 180))
        return (ft_error2("minirt: ambient value out of bound", 1, attr, 0));
    ft_free2(attr);
    return (0);
}

// Light:
// L -40.0,50.0,0.0 0.6 10,0,255
// [iden] [coordinate] [brightness] [colorRGB]
// identifier: L
// x,y,z coordinates of the light point: -40.0,50.0,0.0
// the light brightness ratio in range [0.0,1.0]: 0.6
// (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255
int ft_getLight(t_mrt *mrt, char **attr)
{
    t_light *light;
    if (ft_strncmp(attr[0], "L", 2) == 0 && mrt->light != 0)
        return (ft_error2("minirt: light duplicated", 1, attr, 0));
    light = malloc(sizeof(t_light));
    if (!light)
        return (ft_error2("minirt: parsing light error", 1, attr, 0));
    light->brght = ft_atod(attr[2]);
    if (ft_getVector(&light->crdt, ft_getAttr(attr[1], 3, ','))
        || ft_getColor(&light->color, ft_getAttr(attr[3], 3, ',')))
    {
        free(light);
        mrt->light = 0;
        return (ft_error2("minirt: parsing light color error", 1, attr, 0));
    }
    if (ft_checkValueD(light->brght, 0.0, 1.0) || ft_checkColor(light->color))
    {
        free(light);
        return (ft_error2("minirt: light value out of bound", 1, attr, 0));
    }
    light->next = mrt->light;
    mrt->light = light;
    ft_free2(attr);
    return (0);
}

// Plane:
// pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
// [iden] [coordinate] [rotation vector] [colorRGB]
// identifier: pl
// x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
// 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
// R,G,B colors in range [0-255]: 0,0,225
int ft_getPlane(t_mrt *mrt, char **attr)
{
    t_plane *plane;
    if (ft_strncmp(attr[0], "PL", 3) == 0 && mrt->plane != 0)
        return (ft_error2("minirt: plane duplicated", 1, attr, 0));
    plane = malloc(sizeof(t_plane));
    if (!plane)
        return (ft_error2("minirt: parsing plane error", 1, attr, 0));
    if (ft_getVector(&plane->crdt, ft_getAttr(attr[1], 3, ','))
        || ft_getVector(&plane->rot, ft_getAttr(attr[2], 3, ','))
        || ft_getColor(&plane->color, ft_getAttr(attr[3], 3, ',')))
    {
        free(plane);
        mrt->plane = 0;
        return (ft_error2("minirt: parsing plane color error", 1, attr, 0));
    }
    if (ft_checkVector(plane->rot, -1.0, 1.0) || ft_checkColor(plane->color))
    {
        free(plane);
        return (ft_error2("minirt: plane value out of bound", 1, attr, 0));
    }
    plane->next = mrt->plane;
    mrt->plane = plane;
    ft_free2(attr);
    return (0);
}

// Sphere:
// sp 0.0,0.0,20.6 12.6 10,0,255
// [iden] [coordinate] [diameter] [colorRGB]
// identifier: sp
// x,y,z coordinates of the sphere center: 0.0,0.0,20.6
// the sphere diameter: 12.6
// R,G,B colors in range [0-255]: 10, 0, 255
int ft_getSphere(t_mrt *mrt, char **attr)
{
    t_sphere *sphere;
    if (ft_strncmp(attr[0], "SP", 3) == 0 && mrt->sphere != 0)
        return (ft_error2("minirt: sphere duplicated", 1, attr, 0));
    sphere = malloc(sizeof(t_sphere));
    if (!sphere)
        return (ft_error2("minirt: parsing sphere error", 1, attr, 0));
    sphere->dmt = ft_atod(attr[2]);
    if (ft_getVector(&sphere->crdt, ft_getAttr(attr[1], 3, ','))
        || ft_getColor(&sphere->color, ft_getAttr(attr[3], 3, ',')))
    {
        free(sphere);
        mrt->sphere = 0;
        return (ft_error2("minirt: parsing sphere color error", 1, attr, 0));
    }
    if (ft_checkValueD(sphere->dmt, 0.0, INFINITY) || ft_checkColor(sphere->color))
    {
        free(sphere);
        return (ft_error2("minirt: sphere value out of bound", 1, attr, 0));
    }
    sphere->next = mrt->sphere;
    mrt->sphere = sphere;
    ft_free2(attr);
    return (0);
}

// Cylinder:
// cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
// [iden] [coordinate] [rotation vector] [dmt] [hgt] [colorRGB]
// identifier: cy
// x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
// 3d normalized vector of axis of cylinder. In range [-1,1] for each x,y,z axis:
// 0.0,0.0,1.0
// the cylinder diameter: 14.2
// the cylinder height: 21.42
// R,G,B colors in range [0,255]: 10, 0, 255
int ft_getCylinder(t_mrt *mrt, char **attr)
{
    t_cynd *cylinder;
    if (ft_strncmp(attr[0], "CY", 3) == 0 && mrt->cylinder != 0)
        return (ft_error2("minirt: cylinder dpulicated", 1, attr, 0));
    cylinder = malloc(sizeof(t_cynd));
    if (!cylinder)
        return (ft_error2("minirt: parsing cylinder error", 1, attr, 0));
    cylinder->dmt = ft_atod(attr[3]);
    cylinder->hgt = ft_atod(attr[4]);
    if (ft_getVector(&cylinder->crdt, ft_getAttr(attr[1], 3, ','))
        || ft_getVector(&cylinder->rot, ft_getAttr(attr[2], 3, ','))
        || ft_getColor(&cylinder->color, ft_getAttr(attr[5], 3, ',')))
    {
        free(cylinder);
        mrt->cylinder = 0;
        return (ft_error2("minirt: parsing plane color error", 1, attr, 0));
    }
    if (ft_checkVector(cylinder->rot, -1.0, 1.0) || ft_checkValueD(cylinder->dmt, 0, INFINITY)
        || ft_checkValueD(cylinder->hgt, 0.0, INFINITY) || ft_checkColor(cylinder->color))
    {
        free(cylinder);
        return (ft_error2("minirt: cylinder value out of bound", 1, attr, 0));
    }
    cylinder->next = mrt->cylinder;
    mrt->cylinder = cylinder;
    ft_free2(attr);
    return (0);
}
