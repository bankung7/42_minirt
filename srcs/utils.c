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
    printf("atof : %f\n", n);
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