#include "vector.h"

t_vec3	vec3(double x, double y, double z)
{
	return ((t_vec3){x, y, z});
}

t_vec3	vec3plus(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x + v2.x, v1.y + v2.y, v1.z + v2.z});
}

t_vec3	vec3minus(t_vec3 v1, t_vec3 v2)
{
	return ((t_vec3){v1.x - v2.x, v1.y - v2.y, v1.z - v2.z});
}

t_vec3	vec3mul(t_vec3 v, double n)
{
	return ((t_vec3){v.x * n, v.y * n, v.z * n});
}

t_vec3	vec3div(t_vec3 v, double n)
{
	return (vec3mul(v, 1.0 / n));
}
