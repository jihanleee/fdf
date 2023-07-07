/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:46:06 by jihalee           #+#    #+#             */
/*   Updated: 2023/07/07 16:41:48 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	initialize_vars(t_vars *vars, t_map *map)
{
	vars->map = map;
	reset_position(vars->map, 0);
	vars->map->output = malloc_vectors(vars->map);
	if (vars->map->output == 0)
		return (-1);
	vars->mlx = mlx_init();
	vars->win = mlx_new_window(vars->mlx, 1920, 1080, "fdf");
	vars->img.img = mlx_new_image(vars->mlx, 1920, 1080);
	vars->img.addr = mlx_get_data_addr(vars->img.img,
			&vars->img.bits_per_pixel,
			&vars->img.line_length,
			&vars->img.endian);
	vars->need_update = 1;
	return (0);
}

int	count_rows(char *pathname, t_map *map)
{
	char	buf[1];
	int		fd;

	fd = open(pathname, O_RDWR);
	if (fd == -1)
		return (-1);
	map->n_rows = 0;
	while (read(fd, buf, 1))
	{
		if (buf[0] == '\n')
			(map->n_rows)++;
	}
	close(fd);
	return (0);
}

void	count_cols(t_map *map)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (map->file[0][i])
	{
		while (map->file[0][i] == ' ' && map->file[0][i])
			i++;
		if (map->file[0][i] != ' ' && map->file[0][i])
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

	fd = open(pathname, O_RDWR);
	if (fd == -1 || count_rows(pathname, map) == -1)
		return (ft_printf("invalid file"), -1);
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
	int			i;
	t_vector	**result;

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
