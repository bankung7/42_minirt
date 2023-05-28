#include "minirt.h"

void	putpixel(t_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->llen + x * (data->bpp / 8));
	*(unsigned int *)dst = color;
}

void	setup(t_mrt *mrt)
{
	mrt->width = MRTW;
	mrt->height = MRTH;
	mrt->aspectRatio = (double)mrt->width / mrt->height;
	mrt->mlx.mlx = mlx_init();
	mrt->mlx.mlx_win = mlx_new_window(mrt->mlx.mlx,
			mrt->width, mrt->height, "My minirt");
}

int	render(t_mrt *mrt)
{
	int	i;
	int	j;

	if (!mrt->ambt || !mrt->cam || !mrt->lght)
		return (elog("Not enough info", 1));
	mrt->mlx.img = mlx_new_image(mrt->mlx.mlx, mrt->width, mrt->height);
	mrt->mlx.addr = mlx_get_data_addr(mrt->mlx.img, &mrt->mlx.bpp,
			&mrt->mlx.llen, &mrt->mlx.endian);
	j = 0;
	while (j < mrt->height)
	{
		i = 0;
		while (i < mrt->width)
		{
			putpixel(&mrt->mlx, i, j, trace(mrt, i, j));
			i++;
		}
		j++;
	}
	printf("rendering completed\n");
	mlx_put_image_to_window(mrt->mlx.mlx, mrt->mlx.mlx_win, mrt->mlx.img, 0, 0);
	mlx_hook(mrt->mlx.mlx_win, 2, 1L << 0, m_close, mrt);
	mlx_hook(mrt->mlx.mlx_win, 17, 1L << 0, m_exit, mrt);
	mlx_loop(mrt->mlx.mlx);
	return (0);
}
