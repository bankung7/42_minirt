#include "vector.h"

// vector length
double ft_vecLen(t_vec v)
{
    return (sqrt(ft_vecDot(v, v)));
}

// dot product
double ft_vecDot(t_vec v1, t_vec v2)
{
    return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

// cross product
t_vec ft_vecCross(t_vec v1, t_vec v2)
{
    t_vec v;

    v.x = v1.y * v2.z - v1.z * v2.y;
    v.y = v1.z * v2.x - v1.x * v2.z;
    v.z = v1.x * v2.y - v1.y * v2.x;
    return (v);
}

// normalize vector
t_vec ft_vecNrml(t_vec v)
{
    return (ft_vecDev(v, ft_vecLen(v)));
}

// vector operations
t_vec ft_vecPlus(t_vec v1, t_vec v2)
{
    t_vec v;
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    v.z = v1.z + v2.z;
    return (v);
}

t_vec ft_vecMinus(t_vec v1, t_vec v2)
{
    t_vec v;
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    v.z = v1.z - v2.z;
    return (v);
}

t_vec ft_vecMul(t_vec v1, double n)
{
    t_vec v;
    v.x = v1.x * n;
    v.y = v1.y * n;
    v.z = v1.z * n;
    return (v);
}

t_vec ft_vecDev(t_vec v, double n)
{
    return (ft_vecMul(v, (1 / n)));
}
