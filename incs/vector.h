#ifndef VECTOR_H
#define VECTOR_H

#include <math.h>

typedef struct s_vec3
{
    double x;
    double y;
    double z;
} t_vec3;

t_vec3 vec3(double x, double y, double z);
t_vec3 vec3Plus(t_vec3 v1, t_vec3 v2);
t_vec3 vec3Minus(t_vec3 v1, t_vec3 v2);
t_vec3 vec3Mul(t_vec3 v, double n);
t_vec3 vec3Div(t_vec3 v, double n);
double vec3Dot(t_vec3 v1, t_vec3 v2);
t_vec3 vec3Unit(t_vec3 v);
t_vec3 vec3Cross(t_vec3 v1, t_vec3 v2);
double vec3Len(t_vec3 v);
t_vec3 vec3Mulvec3(t_vec3 v1, t_vec3 v2);

#endif
