/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linear_interpolation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:03:32 by jihalee           #+#    #+#             */
/*   Updated: 2023/07/07 16:27:19 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	rgb_lerp(t_vector a, t_vector b, float t)
{
	int	red;
	int	green;
	int	blue;
	int	color;

	red = a.r + (b.r - a.r) * t;
	green = a.g + (b.g - a.g) * t;
	blue = a.b + (b.b - a.b) * t;
	color = (red << 16) + (green << 8) + blue;
	return (color);
}

int	interpolate(t_vector a, t_vector b, float x, float y)
{
	float	seg_ab;
	float	seg_ap;
	float	t;

	seg_ab = sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
	seg_ap = sqrt(pow(a.x - x, 2) + pow(a.y - y, 2));
	t = seg_ap / seg_ab;
	return (rgb_lerp(a, b, t));
}
