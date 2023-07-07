/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:03:03 by jihalee           #+#    #+#             */
/*   Updated: 2023/07/07 16:36:52 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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

void	connect_vertexes(t_map *map, t_data *img)
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

void	choose_start(t_vector *start, t_vector *end, t_vector v1, t_vector v2)
{
	*start = v1;
	*end = v2;
	if (v1.x > v2.x)
	{
		*start = v2;
		*end = v1;
	}
}

int	is_out_of_bound(t_vector start, t_vector end)
{
	if (start.x < 0 && end.x < 0)
		return (1);
	if (start.x > 1920 && end.x > 1920)
		return (1);
	if (start.y < 0 && end.y < 0)
		return (1);
	if (start.y > 1080 && end.y > 1080)
		return (1);
	return (0);
}

void	draw_segment(t_vector vertex1, t_vector vertex2, t_data *img)
{
	t_vector	start;
	t_vector	end;
	float		slope;

	choose_start(&start, &end, vertex1, vertex2);
	if (is_out_of_bound(start, end))
		return ;
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
