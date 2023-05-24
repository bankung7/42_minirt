#include "vector.h"

t_vec3 vec3(double x, double y, double z)
{
    return ((t_vec3){x, y, z});
}

t_vec3 vec3Plus(t_vec3 v1, t_vec3 v2)
{
    return ((t_vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vec3 vec3Minus(t_vec3 v1, t_vec3 v2)
{
    return ((t_vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_vec3 vec3Mul(t_vec3 v, double n)
{
    return ((t_vec3){v.x * n, v.y * n, v.z * n});
}

t_vec3 vec3Div(t_vec3 v, double n)
{
    return (vec3Mul(v, 1.0 / n));
}

double vec3Dot(t_vec3 v1, t_vec3 v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double vec3Len(t_vec3 v)
{
    return (sqrt(vec3Dot(v, v)));
}

t_vec3 vec3Unit(t_vec3 v)
{
    return (vec3Div(v, vec3Len(v)));
}

t_vec3 vec3Cross(t_vec3 v1, t_vec3 v2)
{
    return ((t_vec3){v1.y * v2.z - v1.z * v2.y
        , v1.z * v2.x - v1.x * v2.z
        , v1.x * v2.y - v1.y * v2.x});
}

t_vec3 vec3Mulvec3(t_vec3 v1, t_vec3 v2)
{
    return ((t_vec3){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z});
}