/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:11:20 by jihalee           #+#    #+#             */
/*   Updated: 2023/07/07 16:30:10 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x > 1920 || y > 1080)
		return ;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	copy_to_output(t_map *map)
{
	int		i;
	int		j;
	float	height;

	height = map->size * map->height;
	i = 0;
	while (i < map->n_rows)
	{
		j = 0;
		while (j < map->n_cols)
		{
			map->output[i][j].x = map->vectors[i][j].x * map->size;
			map->output[i][j].y = map->vectors[i][j].y * map->size;
			map->output[i][j].z = map->vectors[i][j].z * height;
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

int	render_next_frame(t_vars *vars)
{
	if (vars->need_update == 1)
	{
		copy_to_output(vars->map);
		apply_rotation(vars->map);
		translate_vectors(vars->map);
		copy_color(vars->map);
		place_vectors(&vars->img, vars->map);
		connect_vertexes(vars->map, &vars->img);
		mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
		vars->need_update = 0;
	}
	return (0);
}
