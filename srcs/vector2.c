#include "vector.h"

double	vec3dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

double	vec3len(t_vec3 v)
{
	return (sqrt(vec3dot(v, v)));
}

t_vec3	vec3unit(t_vec3 v)
{
	return (vec3div(v, vec3len(v)));
}

t_vec3	vec3cross(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.y * v2.z - v1.z * v2.y
		, v1.z * v2.x - v1.x * v2.z
		, v1.x * v2.y - v1.y * v2.x});
}

t_vec3	vec3mulvec3(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z});
}
