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
int ft_readline(t_mrt *mrt, char *line);
int ft_getAmbient(t_mrt *mrt, char **attr);
int ft_getCamera(t_mrt *mrt, char **attr);
int ft_getLight(t_mrt *mrt, char **attr);
int ft_getPlane(t_mrt *mrt, char **attr);
int ft_getSphere(t_mrt *mrt, char **attr);

// parsing1.c
char **ft_getAttr(char *line, int n, int c);
int ft_getColor(t_color *color, char **attr);
int ft_getVector(t_vec *vec, char **attr);

// utils.c
int ft_arrLen(char **arr);
int ft_printArr(char **arr);
double ft_atod(char *str);

// free.c
int ft_free2(char **arr);
int ft_freeList(t_list *list);
int ft_clean(t_mrt *mrt);

// error.c
int ft_error(char *str, int res);
int ft_error2(char *str, int res, char **f2, char *f1);

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

// test function
void ft_readVector(t_vec vec);
void ft_readSphere(t_mrt *mrt);
void ft_readColor(t_color color);
void ft_readEnv(t_mrt *mrt);

#endif
