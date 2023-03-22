#include "minirt.h"

void ft_info(t_vec v)
{
    printf("x: %f\n", v.x);
    printf("y: %f\n", v.y);
    printf("z: %f\n", v.z);
}

void ft_parr(char **arr)
{
    while (arr && *arr)
    {
        printf("%s\n", *arr);
        arr++;
    }
}

int ft_arrlen(char **arr)
{
    int i = 0;
    if (!arr)
        return (0);
    while (arr && arr[i])
        i++;
    return (i);
}

double ft_atof(char *str)
{
    int sign;
    double n;

    n = 0;
    if (!str)
        return (0);
    sign = 1;
    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            sign = -1;
        str++;
    }
    while (str)
    {
        if (ft_isdigit(*str))
            n = n * 10 + (*str - '0');
        else
            break ;
        str++;
    }
    if (*str == '.' && (str++) != 0 && ft_isdigit(*str))
        n += (double)(*str - '0') / 10;
    n *= sign;
    // printf("atof : %f\n", n);
    return (n);
}

void ft_penv(t_mrt *mrt)
{
    printf("====== Ambient ======\n");
    printf("lighting raito : %.1f\n", mrt->ambt.ratio);
    printf("color : %d %d %d\n\n", mrt->ambt.color.r, mrt->ambt.color.g, mrt->ambt.color.b);

    printf("====== Camera ======\n");
    printf("coordinate : %.1f %.1f %.1f\n", mrt->cam.crdt.x, mrt->cam.crdt.y, mrt->cam.crdt.z);
    printf("3d Vector : %.1f %.1f %.1f\n", mrt->cam.rot.x, mrt->cam.rot.y, mrt->cam.rot.z);
    printf("fov : %d\n\n", mrt->cam.fov);

    printf("====== Lighting ======\n");
    printf("coordinate : %.1f %.1f %.1f\n", mrt->lght.crdt.x, mrt->lght.crdt.y, mrt->lght.crdt.z);
    printf("brightness ratio : %.1f\n", mrt->lght.brght);
    printf("color : %d %d %d\n\n", mrt->lght.color.r, mrt->lght.color.g, mrt->lght.color.b);

}

int ft_error(char *str, int res)
{
    printf("%s\n", str);
    return (res);
}

int ft_error2(char *str, int res, char **f2, char *f1)
{
    if (str)
        printf("%s\n", str);
    if (f2)
        ft_free2(f2);
    if (f1)
        free(f1);
    return (res);
}

// check normal value
int ft_checkFValue(double *n, double min, double max)
{
    if (*n < min || *n > max)
        return (1);
    return (0);
}

int ft_checkIValue(int *n, int min, int max)
{
    if (*n < min || *n > max)
        return (1);
    return (0);
}

// check vector value
int ft_checkVector(t_vec *v, double min, double max)
{
    if (v->x < min || v->y < min || v->z < min)
        return (1);
    if (v->x > max || v->y > max || v->z > max)
        return (1);
    return (0);
}

// check color value
int ft_checkColor(t_color *c)
{
    if (c->r < 0 || c->g < 0 || c->b < 0)
        return (1);
    if (c->r > 255 || c->g > 255 || c->b > 255)
        return (1);
    return (0);
}

// set color
int ft_setColor(t_color *color, char **attr)
{
    if (!attr)
        return (ft_error2("error: color fail", 1, attr, 0));
    color->r = ft_atoi(attr[0]);
    color->g = ft_atoi(attr[1]);
    color->b = ft_atoi(attr[2]);
    ft_free2(attr);
    return (ft_checkColor(color));
}

// set value
int ft_setFValue(double *value, char **arr, double min, double max)
{
    if (!arr)
        return (ft_error2("error: value wrong", 1, arr, 0));
    *value = ft_atof(arr[0]);
    ft_free2(arr);
    return (ft_checkFValue(value, min, max));
}

int ft_setIValue(int *value, char **arr, int min, int max)
{
    if (!arr)
        return (ft_error2("error: value wrong", 1, arr, 0));
    *value = ft_atoi(arr[0]);
    ft_free2(arr);
    return (ft_checkIValue(value, min, max));
}

int ft_setVector(t_vec *vec, char **arr, double min, double max)
{
    if (!arr)
        return (ft_error2("error: crdt wrong", 1, arr, 0));
    vec->x = ft_atof(arr[0]);
    vec->y = ft_atof(arr[1]);
    vec->z = ft_atof(arr[2]);
    ft_free2(arr);
    return (ft_checkVector(vec, min, max));
}

char **ft_getAttr(char *input, int n)
{
    char **attr = ft_split(input, ',');

    if (ft_arrlen(attr) != n)
    {
        ft_free2(attr);
        printf("attr mismatch\n");
        return (0);
    }
    return (attr);
}