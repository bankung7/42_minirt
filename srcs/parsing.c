#include "minirt.h"

// set qcode
int qCode(t_mrt *mrt, int n)
{
    mrt->qcode = n;
    return (mrt->qcode);
}

// get vector
t_vec3 getVec3(t_mrt *mrt, char *str)
{
    char **attr;

    attr = ft_split(str, ',');
    if (arrLen(attr) != 3)
    {
        free2(attr);
        mrt->qcode = 1;
        return (vec3(0, 0, 0));
    }

    t_vec3 vec;
    vec.x = ft_atoi(attr[0]);
    vec.y = ft_atoi(attr[1]);
    vec.z = ft_atoi(attr[2]);
    free2(attr);
    return (vec);
}

int checkInput(t_mrt *mrt, char *line)
{
    char **attr;

    // catch type of input and save in data
    attr = ft_split(line, ' ');
    free(line);
    
    if ((ft_strncmp(attr[0], "A", 2) == 0 || ft_strncmp(attr[0], "a", 2) == 0) && arrLen(attr) == 3)
        getAmbient(mrt, attr);

    free2(attr);
    return (mrt->qcode);
}

int parsing(t_mrt *mrt, char *file)
{
    // check file name
    char *ext = ft_strrchr(file, '.');
    if (ft_strlen(ext) != 3 || ft_strncmp(ext, ".rt", 4))
        return (elog("File not .rt", 1));

    // try open file
    int fd = open(file, O_RDONLY);
    if (fd == -1)
        return (elog("File cannot be opened", 1));
    
    // get line
    char *line = get_next_line(fd);
    while (line)
    {
        if (checkInput(mrt, line))
            break ;
        line = get_next_line(fd);
    }

    // close fd
    close(fd);
    return (mrt->qcode);
}