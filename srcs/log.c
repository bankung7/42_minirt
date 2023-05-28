#include "minirt.h"

int	elog(char *str, int res)
{
	printf("Error\n%s\n", str);
	return (res);
}

int	free2(char **arr, int res)
{
	int	i;

	i = 0;
	while (arr && arr[i])
		free(arr[i++]);
	free(arr);
	return (res);
}

int	clean(t_mrt *mrt, int res)
{
	if (mrt->ambt)
		freelista(mrt->ambt);
	if (mrt->cam)
		freelistc(mrt->cam);
	if (mrt->lght)
		freelistl(mrt->lght);
	if (mrt->obj)
		freelisto(mrt->obj);
	return (res);
}
