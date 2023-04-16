#include "vector.h"

t_vec3 ft_vec3(double x, double y, double z)
{
    return ((t_vec3){x, y, z});
}

t_vec3 ft_vec3Plus(t_vec3 v1, t_vec3 v2)
{
    return ((t_vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vec3 ft_vec3Minus(t_vec3 v1, t_vec3 v2)
{
    return ((t_vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_vec3 ft_vec3Mul(t_vec3 v, double n)
{
    return ((t_vec3){v.x * n, v.y * n, v.z * n});
}

t_vec3 ft_vec3Div(t_vec3 v, double n)
{
    return (ft_vec3Mul(v, 1.0 / n));
}

double ft_vec3Dot(t_vec3 v1, t_vec3 v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3 ft_vec3Cross(t_vec3 a, t_vec3 b)
{
    return ((t_vec3){
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x}
    );
}

double ft_vec3Len(t_vec3 v)
{
    return (sqrt(ft_vec3Dot(v, v)));
}

t_vec3 ft_vec3Unit(t_vec3 v)
{
    return (ft_vec3Div(v, ft_vec3Len(v)));
}