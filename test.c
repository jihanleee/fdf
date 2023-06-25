#include "fdf.h"

int close_window(int keycode, t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > 1920 || y > 1080)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	count_rows(char *pathname, t_map *map)
{
	int		i;
	char	buf[1];
	int		fd;

	fd = open(pathname, O_RDWR);
	map->n_rows = 0;
	while (read(fd, buf, 1))
	{
		if (buf[0] == '\n')
			(map->n_rows)++;
	}
	close(fd);
}

void	count_cols(t_map *map)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while ((map->file)[0][i])
	{
		if ((map->file)[0][i] == ' ')
		{
			count++;
			while ((map->file)[0][i] == ' ')
			i++;
		}
		else
			i++;
	}
	map->n_cols = count + 1;
}

int	readfile(char *pathname, t_map *map)
{
	int	fd;
	int	i;

	count_rows(pathname, map);
	fd = open(pathname, O_RDWR);
	map->file = (char **)ft_calloc(map->n_rows + 1, sizeof (char *));
	if (map->file == 0)
		return (-1);
	i = 0;
	while (i < map->n_rows)
	{
		(map->file)[i] = get_next_line(fd);
		if ((map->file)[i] == 0)
		{
			while (--i >= 0)
				free(map->file[i]);
			return (free(map->file), -1);
		}
		i++;
	}
	(map->file)[i] = 0;
	count_cols(map);
	return (0);
}

int	malloc_vertices(t_map *map)
{
	int	i;

	map->vertices = (t_vertices **)ft_calloc(map->n_rows, sizeof (t_vertices *));
	if (map->vertices == 0)
		return (-1);
	i = 0;
	while (i < map->n_rows)
	{
		map->vertices[i] = (t_vertices *)ft_calloc(map->n_cols, sizeof (t_vertices));
		if (map->vertices[i] == 0)
		{
			while (--i >= 0)
				free(map->vertices[i]);
			return (free(map->vertices), -1);
		}
		i++;
	}
	return (0);
}

void	free_vertices(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->n_rows)
		free(map->vertices[i++]);
	free(map->vertices);
	return ;
}

void	line_to_coor(t_map *map, char **line, int i)
{
	int	j;

	j = 0;
	while (line[j])
	{
		map->vertices[i][j].x = 10 * (j - (map->n_cols / 2));
		map->vertices[i][j].y = 10 * (i - (map->n_rows / 2));
		map->vertices[i][j].z = 1 * (ft_atoi(line[j]));
		j++;
	}
}

int	file_to_coor(t_map *map)
{
	int	i;
	int	j;
	int	k;
	char	**line;

	if (malloc_vertices(map) == -1)
		return (-1);
	i = 0;
	while (map->file[i])
	{
		line = ft_split(map->file[i], ' ');
		if (line == 0)
			return (free_vertices(map), -1);
		line_to_coor(map, line, i);
		free(line);
		i++;
	}
	return (0);
}

void	print_coor(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->n_rows)
	{
		j = 0;
		while (j < map->n_cols)
		{
			ft_printf("(%d, %d, %d)", map->vertices[i][j].x, map->vertices[i][j].y, map->vertices[i][j].z);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	rotate_around_x(t_map *map, double degrees)
{
	double	rad;
	int		i;
	int		j;
	int		y;
	int		z;

	rad = degrees * M_PI / 180;
	i = 0;
	while (i < map->n_rows)
	{
		j = 0;
		while (j < map->n_cols)
		{
			y = map->vertices[i][j].y * cos(rad) - map->vertices[i][j].z * sin(rad);
			z = map->vertices[i][j].y * sin(rad) + map->vertices[i][j].z * cos(rad);
			map->vertices[i][j].y = y;
			map->vertices[i][j].z = z;
			j++;
		}
		i++;
	}
}

void	rotate_around_y(t_map *map, double degrees)
{
	double	rad;
	int		i;
	int		j;
	int		z;
	int		x;

	rad = degrees * M_PI / 180;
	i = 0;
	while (i < map->n_rows)
	{
		j = 0;
		while (j < map->n_cols)
		{
			z = map->vertices[i][j].z * cos(rad) - map->vertices[i][j].x * sin(rad);
			x = map->vertices[i][j].z * sin(rad) + map->vertices[i][j].x * cos(rad);
			map->vertices[i][j].x = x;
			map->vertices[i][j].z = z;
			j++;
		}
		i++;
	}
}

void	rotate_around_z(t_map *map, double degrees)
{
	double	rad;
	int		i;
	int		j;
	int		x;
	int		y;

	rad = degrees * M_PI / 180;
	i = 0;
	while (i < map->n_rows)
	{
		j = 0;
		while (j < map->n_cols)
		{
			x = map->vertices[i][j].x * cos(rad) - map->vertices[i][j].y * sin(rad);
			y = map->vertices[i][j].x * sin(rad) + map->vertices[i][j].y * cos(rad);
			map->vertices[i][j].x = x;
			map->vertices[i][j].y = y;
			j++;
		}
		i++;
	}
}

void	place_vertices(t_data *img, t_map *map)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = 0;
	while (i < map->n_rows)
	{
		j = 0;
		while (j < map->n_cols)
		{
			x = map->vertices[i][j].x + 960;
			y = map->vertices[i][j].y + 540;
			my_mlx_pixel_put(img, x, y, 0x00FF0000);
			j++;
		}
		i++;
	}
}

int	main(void)
{
	t_vars	vars;
	t_data	img;
	t_map	map;
	int		i;
	int		j;
	char	*line;

	if (readfile("./test_maps/42.fdf", &map) == -1)
		return (0);
	if (file_to_coor(&map) == -1)
		return (0);
	print_coor(&map);
	ft_printf("n_row %d, n_col %d", map.n_rows, map.n_cols);
 	rotate_around_y(&map, 45);
	print_coor(&map);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	place_vertices(&img, &map);
	mlx_put_image_to_window(vars.mlx,vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 17, 1L<<0, close_window, &vars);
	mlx_loop(vars.mlx);
}
