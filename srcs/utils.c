#include "minirt.h"

double clamp(double x, double min, double max)
{
    if (x < min)
        return (min);
    if (x > max)
        return (max);
    return (x);
}

int ft_vec3ToColor(t_vec3 v)
{
    // for anti lias
    double scale = 1.0 / 100;
    
    // double scale = 1.0;
    // printf("%.2f %.2f %.2f\n", v.x, v.y, v.z);
    v.x *= scale;
    v.y *= scale;
    v.z *= scale;
    // printf("%.2f %.2f %.2f\n", v.x, v.y, v.z);
    return ((int)(256 * clamp(v.x, 0.0, 0.999)) << 16 | 
        (int)(256 * clamp(v.y, 0.0, 0.999)) << 8 | 
        (int)(256 * clamp(v.z, 0.0, 0.999)));
}

double ft_randDouble(void)
{
    return (rand() / (RAND_MAX + 1.0));
}

double ft_randDoubleRange(double min, double max)
{
    return (min + (max - min) * ft_randDouble());
}

t_vec3 ft_randDoubleVec3(void)
{
    return ((t_vec3){ft_randDouble(),
        ft_randDouble(), ft_randDouble()});
}

t_vec3 ft_randDoubleVec3Range(double min, double max)
{
    return ((t_vec3){ft_randDoubleRange(min, max),
        ft_randDoubleRange(min, max), ft_randDoubleRange(min, max)});
}