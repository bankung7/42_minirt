#include <stdio.h>
#include "minirt.h"

int main(int argc, char **argv)
{
    printf("Welcome to RayTracer\n");
    if (argc != 2)
    {
        printf("./minirt [file.rt]\n");
        return (1);
    }

    // create data
    t_mrt mrt;
    if (!ft_parsing(&mrt , argv[1]))
        return (1);


    return (0);
}