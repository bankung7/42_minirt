#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>
# include <stdbool.h>
# include "mlx.h"
# include "libft.h"
# include "vector.h"
# include "structure.h"

#ifndef W_WIDTH
#define W_WIDTH 1024
#endif

#ifndef CAM_RATIO
#define CAM_RATIO (16 / (double)9)
#endif

// setup.c
int ft_setup(t_mrt *mrt);

// parsing.c
int ft_parsing(t_mrt *mrt, char *file);
int ft_checkline(char *line, t_mrt *mrt);
int ft_getAmbt(char *line, t_mrt *mrt);
int ft_getCam(char *line, t_mrt *mrt);

// utils.c
void ft_info(t_vec v);
void ft_parr(char **arr);
double ft_atof(char *str);
void ft_penv(t_mrt *mrt);
int ft_arrlen(char **arr);

// free.c
void ft_free2(char **arr);

// drawing.c
void ft_mlx_put_pixel(t_data *data, int x, int y, int color);
int ft_makeColor(t_color c);
bool ft_hitSphere(t_vec o, double rd, t_ray r);
int ft_rayColor(t_ray ray);
t_ray ft_createRay(t_cam cam, double u, double v);

#endif
