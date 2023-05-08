#include "minirt.h"

// get ambient
// ∗ identifier: A
// ∗ ambient lighting ratio in range [0.0,1.0]: 0.2
// ∗ R,G,B colors in range [0-255]: 255, 255, 255
int ft_getAmbient(t_mrt *mrt, char **input)
{
    if (ft_arrLen(input) != 3)
        return (ft_log("Error\nAmbient argument fail", 1));

    // get intensity ratio
    mrt->ambt.ratio = ft_getDouble(input[1]);
    if (ft_checkValue(mrt->ambt.ratio, 0.0, 1.0))
        return (ft_log("Error\nAmbient ratio value fail", 1));

    // color
    if (ft_setVec3(&mrt->ambt.color, input[2], 0.0, 255.0))
        return (ft_log("Error\nAmbient color argument fail", 1));
    mrt->ambt.color = ft_vec3Div(mrt->ambt.color, 255);
    printf("Ambient Completed\n");
    return (0);
}

// get camera
// ∗ identifier: C
// ∗ x,y,z coordinates of the view point: -50.0,0,20
// ∗ 3d normalized orientation vector. In range [-1,1] for each x,y,z axis:
// 0.0,0.0,1.0
// ∗ FOV : Horizontal field of view in degrees in range [0,180]: 70
int ft_getCamera(t_mrt *mrt, char **input)
{
    if (ft_arrLen(input) != 4)
        return (ft_log("Error\nCamera argument fail", 1));

    // get coordinate
    if (ft_setVec3(&mrt->cam.orig, input[1], -INFINITY, INFINITY))
        return (ft_log("Error\nCamera coordinate fail", 1));

    // get 3d normal orientation vector
    if (ft_setVec3(&mrt->cam.rot, input[2], -1.0, 1.0))
        return (ft_log("Error\nCamera rotation fail", 1));

    // not sure to normalize it or not
    mrt->cam.rot = ft_vec3Unit(mrt->cam.rot);

    // get fov
    mrt->cam.ifov = ft_atoi(input[3]);
    printf("Camera Completed\n");
    return (0);
}

// get light
// ∗ identifier: L
// ∗ x,y,z coordinates of the light point: -40.0,50.0,0.0
// ∗ the light brightness ratio in range [0.0,1.0]: 0.6
// ∗ (unused in mandatory part)R,G,B colors in range [0-255]: 10, 0, 255
int ft_getLight(t_mrt *mrt, char **input)
{
    if (ft_arrLen(input) != 4)
        return (ft_log("Error\nLight argument fail", 1));

    t_light *lght = malloc(sizeof(t_light));
    if (!lght)
        return (1);
    lght->next = 0;

    // get coordinate
    if (ft_setVec3(&lght->orig, input[1], -INFINITY, INFINITY))
        return (ft_log("Error\nLight coordinate fail", 1));

    // get ratio
    lght->ratio = ft_getDouble(input[2]);
    if (ft_checkValue(lght->ratio, 0.0 , 1.0))
        return (ft_log("Error\nLight ratio fail", 1));

    // color
    if (ft_setVec3(&lght->color, input[3], 0.0, 255.0))
        return (ft_log("Error\nLight color argument fail", 1));
    lght->color = ft_vec3Div(lght->color, 255);

    ft_addLight(&mrt->lght, lght);
    printf("Light Completed\n");
    return (0);
}

// get sphere
// ∗ identifier: sp
// ∗ x,y,z coordinates of the sphere center: 0.0,0.0,20.6
// ∗ the sphere diameter: 12.6
// ∗ R,G,B colors in range [0-255]: 10, 0, 255
int ft_getSphere(t_mrt *mrt, char **input)
{
    if (ft_arrLen(input) != 4)
        return (ft_log("Error\nSphere argument fail", 1));
    // coordinate
    t_object *obj = malloc(sizeof(t_object));
    if (!obj)
        return (1);
    obj->next = 0;
    obj->type = SPHERE;
    if (ft_setVec3(&obj->orig, input[1], -INFINITY, INFINITY))
        return (ft_log("Error\nSphere coordinate fail", 1));

    // diameter
    obj->dmt = ft_getDouble(input[2]);
    if (ft_checkValue(obj->dmt, 0.0 , LIMIT_SIZE))
        return (ft_log("Error\nSphere ratio fail", 1));
    obj->r = obj->dmt / 2.0;

    // color
    if (ft_setVec3(&obj->color, input[3], 0.0, 255.0))
        return (ft_log("Error\nSphere color argument fail", 1));
    obj->color = ft_vec3Div(obj->color, 255);

    ft_addObject(&mrt->obj, obj);

    printf("Sphere Completed\n");
    return (0);
}

// get plane
// ∗ identifier: pl
// ∗ x,y,z coordinates of a point in the plane: 0.0,0.0,-10.0
// ∗ 3d normalized normal vector. In range [-1,1] for each x,y,z axis: 0.0,1.0,0.0
// ∗ R,G,B colors in range [0-255]: 0,0,225
int ft_getPlane(t_mrt *mrt, char **input)
{
    if (ft_arrLen(input) != 4)
        return (ft_log("Error\nPlane argument fail", 1));

    // coordinate
    t_object *obj = malloc(sizeof(t_object));
    if (!obj)
        return (1);
    obj->next = 0;
    obj->type = PLANE;

    if (ft_setVec3(&obj->orig, input[1], -INFINITY, INFINITY))
        return (ft_log("Error\nPlane coordinate fail", 1));

    // normal vector
    if (ft_setVec3(&obj->normal, input[2], -INFINITY, INFINITY))
        return (ft_log("Error\nPlane normal vector fail", 1));

    // color
    if (ft_setVec3(&obj->color, input[3], 0.0, 255.0))
        return (ft_log("Error\nPlane color argument fail", 1));
    obj->color = ft_vec3Div(obj->color, 255);

    ft_addObject(&mrt->obj, obj);
    printf("Plane Completed\n");
    return (0);
}

// get cylinder
// ∗ identifier: cy
// ∗ x,y,z coordinates of the center of the cylinder: 50.0,0.0,20.6
// ∗ 3d normalized vector of axis of cylinder. In range [-1,1] for each x,y,z axis:
// 0.0,0.0,1.0
// ∗ the cylinder diameter: 14.2
// ∗ the cylinder height: 21.42
// ∗ R,G,B colors in range [0,255]: 10, 0, 255
int ft_getCylinder(t_mrt *mrt, char **input)
{
    if (ft_arrLen(input) != 6)
        return (ft_log("Error\nCylinder argument fail", 1));

    // coordinate
    t_object *obj = malloc(sizeof(t_object));
    if (!obj)
        return (1);
    obj->next = 0;
    obj->type = CYLINDER;

    if (ft_setVec3(&obj->orig, input[1], -INFINITY, INFINITY))
        return (ft_log("Error\nCylinder coordinate fail", 1));

    // normal vector
    if (ft_setVec3(&obj->normal, input[2], -1.0, 1.0))
        return (ft_log("Error\nCylinder normal vector fail", 1));

    // diameter
    obj->dmt = ft_getDouble(input[3]);
    if (ft_checkValue(obj->dmt, 0.0 , LIMIT_SIZE))
        return (ft_log("Error\nCylinder diameter fail", 1));
    obj->r = obj->dmt / 2.0;

    // height
    obj->height = ft_getDouble(input[4]);
    if (ft_checkValue(obj->height, 0.0 , LIMIT_SIZE))
        return (ft_log("Error\nCylinder height fail", 1));

    // color
    if (ft_setVec3(&obj->color, input[5], 0.0, 255.0))
        return (ft_log("Error\nCylinder color argument fail", 1));
    obj->color = ft_vec3Div(obj->color, 255);

    ft_addObject(&mrt->obj, obj);
    printf("Cylinder Completed\n");
    return (0);
}
