#include "minirt.h"

// get double
double ft_getDouble(char *str)
{
    double d = 0;
    if ((str[0] == '+' || str[0] == '-') && !ft_isdigit(str[1]))
        return (-INFINITY);
    d = ft_atoi(str);
    char *decimal = ft_strchr(str, '.');
    if (decimal && ft_isdigit(*(++decimal)) == 1)
    {
        if (d > 0 || (d == 0 && str[0] == '+'))
            d += ((*decimal - '0') / 10.0);
        else if (d < 0 || (d == 0 && str[0] == '-'))
            d -= ((*decimal - '0') / 10.0);
        else
            d += ((*decimal - '0') / 10.0);
    }
    // printf("%.1f\n", d);
    return (d);
}

// checkc color
int ft_checkVec3(t_vec3 *vec, double min, double max)
{
    if (vec->x < min || vec->x > max
        || vec->y < min || vec->y > max
        || vec->z < min || vec->z > max)
        return (1);
    return (0);
}

int ft_setVec3(t_vec3 *vec, char *input, double min, double max)
{
    char **attr = ft_getAttr(input, ',', 3);
    if (!attr)
        return (1);
    vec->x = ft_getDouble(attr[0]);
    vec->y = ft_getDouble(attr[1]);
    vec->z = ft_getDouble(attr[2]);
    ft_free2(attr);
    return (ft_checkVec3(vec, min, max));
}


int ft_checkValue(double n, double min, double max)
{
    if (n < min || n > max)
        return (1);
    return (0);
}

int ft_checkAttr(t_mrt *mrt, char **attr)
{
    if (ft_strncmp("A", attr[0], 2) == 0 && ft_arrLen(attr) == 3)
        return (ft_getAmbient(mrt, attr));
    if (ft_strncmp("C", attr[0], 2) == 0 || ft_strncmp("c", attr[0], 2) == 0)
        return (ft_getCamera(mrt, attr));
    if (ft_strncmp("L", attr[0], 2) == 0 || ft_strncmp("l", attr[0], 2) == 0)
        return (ft_getLight(mrt, attr));
    if (ft_strncmp("sp", attr[0], 3) == 0)
        return (ft_getSphere(mrt, attr));
    if (ft_strncmp("pl", attr[0], 3) == 0)
        return (ft_getPlane(mrt, attr));
    if (ft_strncmp("cy", attr[0], 3) == 0)
        return (ft_getCylinder(mrt, attr));
    return (0);
}

char **ft_getAttr(char *input, int delim, int n)
{
    char **attr = ft_split(input, delim);

    if (!attr || (n != 0 && ft_arrLen(attr) != n))
        return (0);
    return (attr);
}

int ft_readline(t_mrt *mrt, int fd)
{
    char *line = get_next_line(fd);
    char **attr;
    while (line)
    {
        // printf("line : %s", line);
        attr = ft_getAttr(line, ' ', 0);
        if (!attr || ft_checkAttr(mrt, attr))
            return (ft_flog(0, 1, attr, line));
        free(line);
        ft_free2(attr);
        line = get_next_line(fd);
    }
    return (0);
}

int ft_parsing(t_mrt *mrt, char *file)
{
    // check the extension of the file
    char *extension = ft_strchr(file, '.');
    if (((int)ft_strlen(file) - (extension - file) != 3) || ft_strncmp(".rt", extension, 4))
    {
        printf("%ld\n", (int)ft_strlen(file) - (extension - file));
        return (ft_log("Error\nFile name : [filename].rt", 1));
    }

    // open file
    int fd = open(file, O_RDONLY);
    if (fd == -1)
        return (ft_log("Error\nCannot Open the file", 1));

    // read each line
    if (ft_readline(mrt, fd))
    {
        close(fd);
        return (1);
    }
    close(fd);
    return (0);
}
