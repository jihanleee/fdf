/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:01:19 by jihalee           #+#    #+#             */
/*   Updated: 2023/07/04 00:39:52 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <mlx_int.h>
# include <unistd.h>
# include <fcntl.h>
# ifndef __USE_MISC
#  define __USE_MISC
# endif
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_vars
{
	t_xvar		*mlx;
	t_win_list	*win;
	t_data		img;
}				t_vars;

typedef struct	s_vectors
{
	float	x;
	float	y;
	float	z;
	int	color;
	int	r;
	int	g;
	int	b;
}				t_vector;

typedef struct s_map
{
	int			n_rows;
	int			n_cols;
	t_vector	r_x;
	t_vector	r_y;
	t_vector	r_z;
	int			center_x;
	int			center_y;
	float		rotation_x;
	float		rotation_y;
	float		rotation_z;
	float		height;
	int			size;
	char		**file;
	t_vector	**vectors;
	t_vector	**output;
}			t_map;

#endif