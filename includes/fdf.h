/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 21:01:19 by jihalee           #+#    #+#             */
/*   Updated: 2023/07/07 16:51:16 by jihalee          ###   ########.fr       */
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

typedef struct s_vectors
{
	float	x;
	float	y;
	float	z;
	int		color;
	int		r;
	int		g;
	int		b;
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
	float		height;
	float		size;
	char		**file;
	t_vector	**vectors;
	t_vector	**output;
}			t_map;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars
{
	t_xvar		*mlx;
	t_win_list	*win;
	t_map		*map;
	t_data		img;
	int			need_update;
}				t_vars;

/*parse_file_1.c*/
int			initialize_vars(t_vars *vars, t_map *map);
int			count_rows(char *pathname, t_map *map);
void		count_cols(t_map *map);
int			readfile(char *pathname, t_map *map);
t_vector	**malloc_vectors(t_map *map);

/*parse_file_2.c*/
int			get_color(char *line);
void		line_to_coor(t_map *map, char **line, int i);
int			file_to_coor(t_map *map);

/*end_processs.c*/
void		free_map(t_map *map);
void		free_vectors(t_map *map, t_vector **vectors);
int			close_window(t_vars *vars);

/*linear_interpolation.c*/
int			rgb_lerp(t_vector a, t_vector b, float t);
int			interpolate(t_vector a, t_vector b, float x, float y);

/*draw.c*/
void		place_vectors(t_data *img, t_map *map);
void		connect_vertexes(t_map *map, t_data *img);
void		choose_start(t_vector *s, t_vector *e, t_vector v1, t_vector v2);
int			is_out_of_bound(t_vector start, t_vector end);
void		draw_segment(t_vector vertex1, t_vector vertex2, t_data *img);

/*bresenham.c*/
void		octant_1(t_vector start, t_vector end, t_data *img, float slope);
void		octant_8(t_vector start, t_vector end, t_data *img, float slope);
void		octant_2(t_vector start, t_vector end, t_data *img, float slope);
void		octant_7(t_vector start, t_vector end, t_data *img, float slope);
void		vertical_line(t_vector vertex1, t_vector vertex2, t_data *img);

/*matrix_1.c*/
t_vector	set_vector(float x, float y, float z);
t_vector	rotate_vector_x(t_vector r, float rad);
t_vector	rotate_vector_y(t_vector r, float rad);
t_vector	rotate_vector_z(t_vector r, float rad);
void		unit_rotation(t_map *m, t_vector (*r)(t_vector, float), float rad);

/*matrix_2.c*/
t_vector	mtrx_transform(t_vector v, t_vector a, t_vector b, t_vector c);
void		apply_rotation(t_map *map);
void		translate_vectors(t_map *map);
void		reset_position(t_map *map, int isometric);

/*render.c*/
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
int			render_next_frame(t_vars *vars);
void		copy_color(t_map *map);
void		copy_to_output(t_map *map);

/*key_hook.c*/
void		key_hook_rotation(int keycode, t_vars *vars);
void		key_hook_translation(int keycode, t_vars *vars);
void		key_hook_zoom(int keycode, t_vars *vars);
int			key_hook(int keycode, t_vars *vars);

#endif