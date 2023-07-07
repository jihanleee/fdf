/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:01:51 by jihalee           #+#    #+#             */
/*   Updated: 2023/07/07 16:34:37 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
		color = interpolate(start, end, x + start.x, slope * x + start.y);
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
	while (y + start.y <= end.y)
	{
		color = interpolate(start, end, start.x, y + start.y);
		my_mlx_pixel_put(img, start.x, y + start.y, color);
		y++;
	}
}
