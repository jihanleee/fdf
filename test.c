#include "fdf.h"

int close_window(/* int keycode, */ t_vars *vars)
{

/* 	mlx_clear_window(vars->mlx, vars->win); */
	mlx_destroy_window(vars->mlx, vars->win);
	((t_xvar *)(vars->mlx))->end_loop = 1;
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
		while ((map->file)[0][i] == ' ' && (map->file)[0][i])
			i++;
		if ((map->file)[0][i] != ' ' && (map->file)[0][i])
		{
			count++;
			while (map->file[0][i] != ' ' && map->file[0][i])
				i++;
		}
	}
	map->n_cols = count;
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

t_vector	**malloc_vectors(t_map *map)
{
	int	i;
	t_vector **result;

	result = (t_vector **)ft_calloc(map->n_rows, sizeof (t_vector *));
	if (result == 0)
		return (NULL);
	i = 0;
	while (i < map->n_rows)
	{
		result[i] = (t_vector *)ft_calloc(map->n_cols, sizeof (t_vector));
		if (result[i] == 0)
		{
			while (--i >= 0)
				free(result[i]);
			return (free(result), NULL);
		}
		i++;
	}
	return (result);
}

void	free_vectors(t_map *map, t_vector **vectors)
{
	int	i;

	i = 0;
	while (i < map->n_rows)
		free(vectors[i++]);
	free(vectors);
	return ;
}

char	*ft_strlowcase(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'A' && str[i] <= 'Z'))
			str[i] += 32;
		i++;
	}
	return (str);
}

int	get_color(t_map *map, char *line)
{
	int	i;

	ft_strlowcase(line);
	i = 0;
	while (line[i] != ',' && line[i])
		i++;
	if (line[i] == 0)
		return (0x00FFFFFF);
	else if (line[i] == ',')
	i += 3;
	return (ft_atoi_base(&(line[i]), "0123456789abcdef"));
}

void	color_to_rgb(t_vector *vector)
{
	int				color;

	color = vector->color;
	vector->b = (color) & 0xff;
	vector->g = (color>>8) & 0xff;
	vector->r = (color>>16) & 0xff;
}

void	line_to_coor(t_map *map, char **line, int i)
{
	int	j;

	j = 0;
	while (j < map->n_cols)
	{
		map->vectors[i][j].x = (j - (map->n_cols / 2));
		map->vectors[i][j].y = (i - (map->n_rows / 2));
		map->vectors[i][j].z = (ft_atoi(line[j]));
		map->vectors[i][j].color = get_color(map, line[j]);
		color_to_rgb(&(map->vectors[i][j]));
		j++;
	}
}

int	file_to_coor(t_map *map)
{
	int	i;
	int	j;
	int	k;
	char	**line;

	map->vectors = malloc_vectors(map);
	if (map->vectors == 0)
		return (-1);
	i = 0;
	while (i < map->n_rows)
	{
		line = ft_split(map->file[i], ' ');
		if (line == 0)
			return (free_vectors(map, map->vectors), -1);
		line_to_coor(map, line, i);
		j = 0;
		while (line[j])
		{
			free(line[j++]);
		}
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
			ft_printf("(%d, %d, %d)", map->vectors[i][j].x, map->vectors[i][j].y, map->vectors[i][j].z);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

int	rgb_lerp(t_vector a, t_vector b, float t)
{
	int	red;
	int	green;
	int	blue;
	int	color;

	red = a.r + (b.r - a.r) * t;
	green = a.g + (b.g - a.g) * t;
	blue = a.b + (b.b - a.b) * t;
	color = (red<<16) + (green<<8) + blue;
	return (color);
}

int	interpolate(t_vector a, t_vector b, float x, float y)
{
	int		output;
	float	x1;
	float	x2;
	float	y1;
	float	y2;
	float	seg_ab;
	float	seg_ap;
	float	t;

	x1 = a.x;
	y1 = a.y;
	x2 = b.x;
	y2 = b.y;
	seg_ab = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	seg_ap = sqrt(pow(x1 - x, 2) + pow(y1 - y, 2));
	t = seg_ap / seg_ab;
	return (rgb_lerp(a, b, t));
}

void	place_vectors(t_data *img, t_map *map)
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
			x = round(map->output[i][j].x);
			y = round(map->output[i][j].y);
			my_mlx_pixel_put(img, x, y, map->output[i][j].color);
			j++;
		}
		i++;
	}
}

void	octant_1(t_vector start, t_vector end, t_data *img, float slope)
{
	int		x;
	int		t;
	int		color;
	x = 0;
	t = start.y;
	while (x + start.x <= end.x)
	{

		if (slope * (float)x + (float)start.y >= (float)t + 0.5)
			t++;
		color = interpolate(start, end, x + start.x, slope * x + start.y);
 		my_mlx_pixel_put(img, x + start.x, t, color);
		x++;
	}
}

void	octant_8(t_vector start, t_vector end, t_data *img, float slope)
{
	int	x;
	int	t;
	int	color;

	x = 0;
	t = start.y;
	while (x + start.x <= end.x)
	{
		if (slope * (float)x + (float)start.y <= (float)t - 0.5)
			t--;
		color = interpolate(start, end, x + start.x, slope * (float)x + (float)start.y);
 		my_mlx_pixel_put(img, x + start.x, t, color);
		x++;
	}
}

void	octant_2(t_vector start, t_vector end, t_data *img, float slope)
{
	int		y;
	int		t;
	int		color;

	y = 0;
	t = start.x;
	while (y + start.y <= end.y)
	{
		if ((float)y / slope + (float)start.x >= (float)t + 0.5)
			t++;
		color = interpolate(start, end, y / slope + start.x, y + start.y);
		my_mlx_pixel_put(img, t, y + start.y, color);
		y++;
	}
}

void	octant_7(t_vector start, t_vector end, t_data *img, float slope)
{
	int		y;
	int		t;
	int		color;

	y = 0;
	t = start.x;
	while (y + start.y >= end.y)
	{
		if ((float)y / slope + (float)start.x >= (float)t + 0.5)
			t++;
		color = interpolate(start, end, y / slope + start.x, y + start.y);
		my_mlx_pixel_put(img, t, y + start.y, color);
		y--;
	}
}

void	vertical_line(t_vector vertex1, t_vector vertex2, t_data *img)
{
	t_vector	start;
	t_vector	end;
	int			y;
	int			color;

	start = vertex1;
	end = vertex2;
	if (vertex1.y > vertex2.y)
	{
		start = vertex2;
		end = vertex1;
	}
	y = 0;
	while(y + start.y <= end.y)
	{
		color = interpolate(start, end, start.x, y + start.y);
		my_mlx_pixel_put(img, start.x, y + start.y, color);
		y++;
	}
}

void	draw_segment(t_vector vertex1, t_vector vertex2, t_data *img)
{
	t_vector	start;
	t_vector	end;
	float		slope;

	start = vertex1;
	end = vertex2;
	if (vertex1.x > vertex2.x)
	{
		start = vertex2;
		end = vertex1;
	}
	if (start.x == end.x)
	{
		vertical_line(vertex1, vertex2, img);
		return ;
	}
	slope = ((float)start.y - (float)end.y) / ((float)start.x - (float)end.x);
	if (slope >= 1)
		octant_2(start, end, img, slope);
 	else if (slope >= 0 && slope < 1)
		octant_1(start, end, img, slope);
	else if (slope < 0 && slope >= -1)
		octant_8(start, end, img, slope);
	else
		octant_7(start, end, img, slope);
}

void	connect_vector(t_map *map, t_data *img)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->n_rows - 1)
	{
		j = 0;
		while (j < map->n_cols - 1)
		{
			draw_segment(map->output[i][j], map->output[i + 1][j], img);
			draw_segment(map->output[i][j], map->output[i][j + 1], img);
			j++;
		}
		i++;
	}
	i = -1;
	while (++i < map->n_rows - 1)
		draw_segment(map->output[i][j], map->output[i + 1][j], img);
	j = -1;
	while (++j < map->n_cols - 1)
		draw_segment(map->output[i][j], map->output[i][j + 1], img);		
}

t_vector	set_vector(float x, float y, float z)
{
	t_vector	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
}

int	initialize_map(t_map *map)
{
	map->center_x = 960;
	map->center_y = 540;
	map->rotation_x = asin(sqrt(3) / 3);
	map->rotation_y = 0;
	map->rotation_z = M_PI / 4;
	map->size = (1200) / map->n_cols;
	map->height = (float)map->size / 6;
	map->output = malloc_vectors(map);
	map->r_x = set_vector(1, 0, 0);
	map->r_y = set_vector(0, 1, 0);
	map->r_z = set_vector(0, 0, 1);
	if (map->output == 0)
		return (-1);
	return (0);
}

void	translate_vectors(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->n_rows)
	{
		j = 0;
		while (j < map->n_cols)
		{
			map->output[i][j].x += map->center_x;
			map->output[i][j].y += map->center_y;
			j++;
		}
		i++;
	}
}

void	copy_to_output(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->n_rows)
	{
		j = 0;
		while (j < map->n_cols)
		{
			map->output[i][j].x = map->vectors[i][j].x;
			map->output[i][j].y = map->vectors[i][j].y;
			map->output[i][j].z = map->vectors[i][j].z;
			j++;
		}
		i++;
	}
}

void	copy_color(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->n_rows)
	{
		j = 0;
		while (j < map->n_cols)
		{
			map->output[i][j].color = map->vectors[i][j].color;
			map->output[i][j].r = map->vectors[i][j].r;
			map->output[i][j].g = map->vectors[i][j].g;
			map->output[i][j].b = map->vectors[i][j].b;
			j++;
		}
		i++;
	}
}

t_vector	rotate_vector_x(t_vector r, float rad)
{
	float	y;
	float	z;

	y = r.y * cos(rad) - r.z * sin(rad);
	z = r.y * sin(rad) + r.z * cos(rad);
	return (set_vector(r.x, y, z));
}

t_vector	rotate_vector_y(t_vector r, float rad)
{
	float	z;
	float	x;

	z = r.z * cos(rad) - r.x * sin(rad);
	x = r.z * sin(rad) + r.x * cos(rad);
	return (set_vector(x, r.y, z));
}

t_vector	rotate_vector_z(t_vector r, float rad)
{
	float	x;
	float	y;

	x = r.x * cos(rad) - r.y * sin(rad);
	y = r.x * sin(rad) + r.y * cos(rad);
	return (set_vector(x, y, r.z));	
}

t_vector	unit_rotation(t_map *map, t_vector (*rotate)(t_vector, float), float rad)
{
	map->r_x = rotate(map->r_x, rad);
	map->r_y = rotate(map->r_y, rad);
	map->r_z = rotate(map->r_z, rad);
}

t_vector	mtrx_transform(t_vector v, t_vector a, t_vector b, t_vector c)
{
	float	x;
	float	y;
	float	z;

	x = a.x * v.x + b.x * v.y + c.x * v.z;
	y = a.y * v.x + b.y * v.y + c.y * v.z;
	z = a.z * v.x + b.z * v.y + c.z * v.z;

	return (set_vector(x, y, z));
}

void	apply_rotation(t_map *map)
{
	int	i;
	int	j;
	t_vector	x;
	t_vector	y;
	t_vector	z;

	x = map->r_x;
	y = map->r_y;
	z = map->r_z;

	i = 0;
	while (i < map->n_rows)
	{
		j = 0;
		while (j < map->n_cols)
		{
			map->output[i][j] = mtrx_transform(map->output[i][j], x, y, z);
			j++;
		}
		i++;
	}
}

void	unit_resize(t_map *map)
{
	map->r_x.x *= map->size;
	map->r_y.y *= map->size;
	map->r_z.z *= map->height;
}

void	update_frame(t_map *map, t_data *img, t_vars *vars)
{
	copy_to_output(map);
	unit_resize(map);
	unit_rotation(map, rotate_vector_z, map->rotation_z);
	unit_rotation(map, rotate_vector_x, map->rotation_x);
	unit_rotation(map, rotate_vector_y, map->rotation_y);
	apply_rotation(map);
	translate_vectors(map);
	copy_color(map);
	place_vectors(img, map);
	connect_vector(map, img);
	mlx_put_image_to_window(vars->mlx, vars->win, img->img, 0, 0);
}

int	main(void)
{
	t_vars	vars;
	t_data	img;
	t_map	map;

	if (readfile("./test_maps/t1.fdf", &map) == -1)
		return (0);
	if (file_to_coor(&map) == -1 || initialize_map (&map) == -1)
		return (0);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "fdf");
	vars.img.img = mlx_new_image(vars.mlx, 1920, 1080);
	vars.img.addr = mlx_get_data_addr(vars.img.img, &vars.img.bits_per_pixel, &vars.img.line_length,
								&vars.img.endian);
	update_frame(&map, &vars.img, &vars);
	mlx_hook(vars.win, 17, 1L<<17, close_window, &vars);
	mlx_loop(vars.mlx);
}
