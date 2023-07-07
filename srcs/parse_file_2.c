/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihalee <jihalee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 15:47:24 by jihalee           #+#    #+#             */
/*   Updated: 2023/07/07 16:42:42 by jihalee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*ft_strlowcase(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if ((str[i] >= 'A' && str[i] <= 'Z'))
			str[i] += 32;
		i++;
	}
	return (str);
}

int	get_color(char *line)
{
	int	i;

	ft_strlowcase(line);
	i = 0;
	while (line[i] != ',' && line[i])
		i++;
	if (line[i] == 0)
		return (0x00FFFFFF);
	else if (line[i] == ',')
	i += 3;
	return (ft_atoi_base(&(line[i]), "0123456789abcdef"));
}

void	line_to_coor(t_map *map, char **line, int i)
{
	int	j;
	int	color;

	j = 0;
	while (j < map->n_cols)
	{
		map->vectors[i][j].x = (j - (map->n_cols / 2));
		map->vectors[i][j].y = (i - (map->n_rows / 2));
		map->vectors[i][j].z = (ft_atoi(line[j]));
		map->vectors[i][j].color = get_color(line[j]);
		color = map->vectors[i][j].color;
		map->vectors[i][j].b = (color) & 0xff;
		map->vectors[i][j].g = (color >> 8) & 0xff;
		map->vectors[i][j].r = (color >> 16) & 0xff;
		j++;
	}
}

int	file_to_coor(t_map *map)
{
	int		i;
	int		j;
	char	**line;

	map->vectors = malloc_vectors(map);
	if (map->vectors == 0)
		return (-1);
	i = 0;
	while (i < map->n_rows)
	{
		line = ft_split(map->file[i], ' ');
		if (line == 0)
			return (free_vectors(map, map->vectors), -1);
		line_to_coor(map, line, i);
		j = 0;
		while (line[j])
		{
			free(line[j++]);
		}
		free(line);
		i++;
	}
	return (0);
}
