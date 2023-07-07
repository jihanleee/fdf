/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:11:45 by jihalee           #+#    #+#             */
/*   Updated: 2023/07/07 16:40:00 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	main(int ac, char **av)
{
	t_vars	vars;
	t_map	map;

	if (ac != 2)
		return (ft_printf("./fdf [map path]\n"), 0);
	if (readfile(av[1], &map) == -1)
		return (0);
	if (file_to_coor(&map) == -1 || initialize_vars(&vars, &map) == -1)
		return (0);
	render_next_frame(&vars);
	mlx_key_hook(vars.win, key_hook, &vars);
	mlx_loop_hook(vars.mlx, render_next_frame, &vars);
	mlx_hook(vars.win, 17, 1L << 17, close_window, &vars);
	mlx_loop(vars.mlx);
}
