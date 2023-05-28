#include "minirt.h"

// set qcode
int	qcode(t_mrt *mrt, int n)
{
	mrt->qcode = n;
	return (mrt->qcode);
}

int	check_input(t_mrt *mrt, char *line)
{
	char	**attr;

	attr = ft_split(line, ' ');
	free(line);
	if (ft_strncmp(attr[0], "A", 2) == 0 && arr_len(attr) == 3)
		return (getambient(mrt, attr, 1));
	if (ft_strncmp(attr[0], "a", 2) == 0 && arr_len(attr) == 3)
		return (getambient(mrt, attr, 0));
	if (ft_strncmp(attr[0], "C", 2) == 0 && arr_len(attr) == 4)
		return (getCamera(mrt, attr, 1));
	if (ft_strncmp(attr[0], "c", 2) == 0 && arr_len(attr) == 4)
		return (getCamera(mrt, attr, 0));
	if (ft_strncmp(attr[0], "L", 2) == 0 && arr_len(attr) == 4)
		return (getlight(mrt, attr, 1));
	if (ft_strncmp(attr[0], "l", 2) == 0 && arr_len(attr) == 4)
		return (getlight(mrt, attr, 0));
	get_object(mrt, attr);
	return (mrt->qcode);
}

int	parsing(t_mrt *mrt, char *file)
{
	char	*ext;
	char	*line;
	int		fd;

	ext = ft_strrchr(file, '.');
	if (ft_strlen(ext) != 3 || ft_strncmp(ext, ".rt", 4))
		return (elog("File not .rt", 1));
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (elog("File cannot be opened", 1));
	line = get_next_line(fd);
	while (line)
	{
		if (check_input(mrt, line))
			break ;
		line = get_next_line(fd);
	}
	close(fd);
	return (mrt->qcode);
}
