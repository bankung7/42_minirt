#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <errno.h>
# include "mlx.h"
# include "libft.h"
# include "vector.h"
# include "structure.h"

// parsing.c
int ft_parsing(t_mrt *mrt, char *file);
int ft_checkline(char *line, t_mrt *mrt);
int ft_getAmbt(char *line, t_mrt *mrt);

// utils.c
void ft_info(t_vector v);
void ft_parr(char **arr);
double ft_atof(char *str);

// free.c
void ft_free2(char **arr);

#endif
