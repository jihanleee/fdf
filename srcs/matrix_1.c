/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:07:35 by jihalee           #+#    #+#             */
/*   Updated: 2023/07/07 16:41:21 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vector	set_vector(float x, float y, float z)
{
	t_vector	result;

	result.x = x;
	result.y = y;
	result.z = z;
	return (result);
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

void	unit_rotation(t_map *map, t_vector (*r)(t_vector, float), float rad)
{
	map->r_x = r(map->r_x, rad);
	map->r_y = r(map->r_y, rad);
	map->r_z = r(map->r_z, rad);
}
