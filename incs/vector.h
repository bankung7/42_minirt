#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

typedef struct s_vec
{
    double x;
    double y;
    double z;
} t_vec;

double ft_vecLen(t_vec v);
double ft_vecDot(t_vec v1, t_vec v2);
t_vec ft_vecCross(t_vec v1, t_vec v2);
t_vec ft_vecPlus(t_vec v1, t_vec v2);
t_vec ft_vecMinus(t_vec v1, t_vec v2);
t_vec ft_vecMul(t_vec v1, double n);
t_vec ft_vecDev(t_vec v1, double n);
t_vec ft_vecNrml(t_vec v);

#endif
