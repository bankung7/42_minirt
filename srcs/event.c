#include "minirt.h"

int	m_close(int keycode, t_mrt *mrt)
{
	if (keycode == 53)
	{
		mlx_destroy_window(mrt->mlx.mlx, mrt->mlx.mlx_win);
		clean(mrt, 0);
		exit(0);
	}
	// if (keycode == 8)
	// 	return (switch_cam(mrt));
	return (0);
}

int	m_exit(t_mrt *mrt)
{
	mlx_destroy_window(mrt->mlx.mlx, mrt->mlx.mlx_win);
	clean(mrt, 0);
	exit(0);
	return (0);
}
