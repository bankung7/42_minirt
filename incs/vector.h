/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:16:05 by pjerddee          #+#    #+#             */
/*   Updated: 2023/05/28 16:16:07 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include <math.h>

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

t_vec3	vec3(double x, double y, double z);
t_vec3	vec3plus(t_vec3 v1, t_vec3 v2);
t_vec3	vec3minus(t_vec3 v1, t_vec3 v2);
t_vec3	vec3mul(t_vec3 v, double n);
t_vec3	vec3div(t_vec3 v, double n);
double	vec3dot(t_vec3 v1, t_vec3 v2);
t_vec3	vec3unit(t_vec3 v);
t_vec3	vec3cross(t_vec3 v1, t_vec3 v2);
double	vec3len(t_vec3 v);
t_vec3	vec3mulvec3(t_vec3 v1, t_vec3 v2);

#endif
