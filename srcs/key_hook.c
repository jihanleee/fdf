/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hook.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:05:10 by jihalee           #+#    #+#             */
/*   Updated: 2023/07/07 16:30:43 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	key_hook_rotation(int keycode, t_vars *vars)
{
	if (keycode == 65431)
		unit_rotation(vars->map, rotate_vector_x, M_PI_4 / 4);
	if (keycode == 65437)
		unit_rotation(vars->map, rotate_vector_x, -1 * M_PI_4 / 4);
	if (keycode == 65430)
		unit_rotation(vars->map, rotate_vector_y, -1 * M_PI_4 / 4);
	if (keycode == 65432)
		unit_rotation(vars->map, rotate_vector_y, M_PI_4 / 4);
	if (keycode == 65429)
		unit_rotation(vars->map, rotate_vector_z, -1 * M_PI_4 / 4);
	if (keycode == 65434)
		unit_rotation(vars->map, rotate_vector_z, M_PI_4 / 4);
}

void	key_hook_translation(int keycode, t_vars *vars)
{
	if (keycode == 119)
		vars->map->center_y -= 60;
	if (keycode == 115)
		vars->map->center_y += 60;
	if (keycode == 97)
		vars->map->center_x -= 60;
	if (keycode == 100)
		vars->map->center_x += 60;
}

void	key_hook_zoom(int keycode, t_vars *vars)
{
	if (keycode == 65451)
		vars->map->size *= 1.2;
	if (keycode == 65453 && vars->map->size > 1)
		vars->map->size *= 0.8;
	if (keycode == 65455)
		vars->map->height *= 1.1;
	if (keycode == 65450)
		vars->map->height *= 0.9;
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == 65307)
		close_window(vars);
	mlx_destroy_image(vars->mlx, vars->img.img);
	vars->img.img = mlx_new_image(vars->mlx, 1920, 1080);
	vars->img.addr = mlx_get_data_addr(vars->img.img,
			&(vars->img.bits_per_pixel),
			&(vars->img.line_length),
			&(vars->img.endian));
	if (keycode == 114)
		reset_position(vars->map, 0);
	if (keycode == 105)
		reset_position(vars->map, 1);
	key_hook_rotation(keycode, vars);
	key_hook_translation(keycode, vars);
	key_hook_zoom(keycode, vars);
	vars->need_update = 1;
	return (0);
}
