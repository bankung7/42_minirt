/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:13:43 by pjerddee          #+#    #+#             */
/*   Updated: 2023/05/28 16:13:47 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}

// get vector
t_vec3	getvec3(t_mrt *mrt, char *str, int div)
{
	char	**attr;
	t_vec3	vec;

	attr = ft_split(str, ',');
	if (arr_len(attr) != 3)
	{
		free2(attr, 0);
		mrt->qcode = 1;
		return (vec3(0, 0, 0));
	}
	vec.x = ft_atoi(attr[0]);
	vec.y = ft_atoi(attr[1]);
	vec.z = ft_atoi(attr[2]);
	vec = vec3div(vec, div);
	free2(attr, 0);
	return (vec);
}

double	getdouble(char *str)
{
	int		sign;
	int		e;
	double	n;

	e = 1;
	n = ft_atoi(str);
	sign = 1;
	if (str[0] == '-')
	{
		str++;
		sign = -1;
	}
	while (ft_isdigit(*str) == 1)
		str++;
	if (*str != '.')
		return (n);
	while (ft_isdigit(*(++str)))
		n += ((*str - '0') / pow(10.0, e++)) * sign;
	return (n);
}

int	checkvalue(t_mrt *mrt, double n, double min, double max)
{
	if (n < min || n > max)
		mrt->qcode = 1;
	return (0);
}

int	checkvec3(t_mrt *mrt, t_vec3 v, double min, double max)
{
	if (v.x < min || v.x > max
		|| v.y < min || v.y > max
		|| v.z < min || v.z > max)
		mrt->qcode = 1;
	return (0);
}
