/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:08:46 by jihalee           #+#    #+#             */
/*   Updated: 2023/07/07 16:31:22 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	reset_position(t_map *map, int isometric)
{
	map->r_x = set_vector(1, 0, 0);
	map->r_y = set_vector(0, 1, 0);
	map->r_z = set_vector(0, 0, 1);
	if (isometric == 1)
	{
		unit_rotation(map, rotate_vector_z, M_PI / 4);
		unit_rotation(map, rotate_vector_x, asin(sqrt(3) / 3));
	}
	if (isometric == 0)
		map->height = 0.6;
	map->center_x = 960;
	map->center_y = 540;
	map->size = (1200) / map->n_cols;
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

void	apply_rotation(t_map *map)
{
	int			i;
	int			j;
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
