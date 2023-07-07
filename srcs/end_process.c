/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end_process.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:49:37 by jihalee           #+#    #+#             */
/*   Updated: 2023/07/07 16:37:16 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_vectors(t_map *map, t_vector **vectors)
{
	int	i;

	i = 0;
	while (i < map->n_rows)
		free(vectors[i++]);
	free(vectors);
	return ;
}

void	free_map(t_map *map)
{
	int	i;

	free_vectors(map, map->vectors);
	free_vectors(map, map->output);
	i = 0;
	while (i < map->n_rows)
		free(map->file[i++]);
	free(map->file);
}

int	close_window(t_vars *vars)
{
	free_map(vars->map);
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_window(vars->mlx, vars->win);
	mlx_destroy_display(vars->mlx);
	free(vars->mlx);
	exit(0);
	return (0);
}
