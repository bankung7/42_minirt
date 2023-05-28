/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjerddee <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/28 16:14:56 by pjerddee          #+#    #+#             */
/*   Updated: 2023/05/28 16:14:58 by pjerddee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	m_exit(t_mrt *mrt)
{
	mlx_destroy_window(mrt->mlx.mlx, mrt->mlx.mlx_win);
	clean(mrt, 0);
	exit(0);
	return (0);
}

int	m_close(int keycode, t_mrt *mrt)
{
	if (keycode == 53)
		return (m_exit(mrt));
	if (keycode == 8)
		return (switch_cam(mrt));
	return (0);
}
