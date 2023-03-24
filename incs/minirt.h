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
#define W_WIDTH 800
#endif

#ifndef CAM_RATIO
#define CAM_RATIO (16.0 / 9.0)
#endif

#ifndef W_HEIGHT
#define W_HEIGHT (int)(W_WIDTH / CAM_RATIO)
#endif

// render.c
int ft_setup(t_mrt *mrt);
int ft_recal(t_mrt *mrt);
void ft_render(t_mrt *mrt);

// parsing.c
int ft_parsing(t_mrt *mrt, char *file);
int ft_checkline(char *line, t_mrt *mrt);
int ft_getAmbient(char **arr, t_mrt *mrt);
int ft_getCamera(char **arr, t_mrt *mrt);
int ft_getLight(char **arr, t_mrt *mrt);
int ft_getPlane(char **arr, t_mrt *mrt);
int ft_getSphere(char **arr, t_mrt *mrt);

// utils.c
void ft_info(t_vec v);
void ft_parr(char **arr);
double ft_atof(char *str);
void ft_penv(t_mrt *mrt);
int ft_arrlen(char **arr);
int ft_error(char *str, int res);
int ft_error2(char *str, int res, char **f2, char *f1);

int ft_checkFValue(double *n, double min, double max);
int ft_checkIValue(int *n, int min, int max);
int ft_checkColor(t_color *c);
int ft_checkVector(t_vec *v, double min, double max);

int ft_setColor(t_color *color, char **arr);
int ft_setFValue(double *value, char **arr, double min, double max);
int ft_setIValue(int *value, char **arr, int min, int max);
int ft_setVector(t_vec *vec, char **arr, double min, double max);

char **ft_getAttr(char *input, int n);

// free.c
int ft_free2(char **arr);

// drawing.c
void ft_mlx_put_pixel(t_data *data, int x, int y, int color);
int ft_makeColor(t_color c);
double ft_hitSphere(t_vec o, double rd, t_ray r);
int ft_rayColor(t_mrt *mrt, t_ray ray);
t_ray ft_createRay(t_cam cam, double u, double v);
double ft_convertVP(t_mrt *mrt, double n);
t_vec ft_convertVec(t_mrt *mrt, t_vec v);

// hook.c
int	ft_keyhook(int keycode, t_mrt *mrt);
int ft_recal(t_mrt *mrt);
int ft_close(t_mrt *mrt);

#endif
