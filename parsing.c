/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:19:49 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/02 15:31:36 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	parse_every_single_char(t_map *map, int y, int fd)
{
	int		x;
	char	**values;
	char	*line;
	int		i;
	t_point	*point;

	line = get_next_line(fd);
	values = ft_split(line, ' ');
	free(line);
	x = 0;
	i = 0;
	if (!values)
		return (-1);
	while (values[i])
	{
		point = &(map->points[y][x]);
		point->cart_x = x;
		point->cart_y = y;
		point->cart_z = ft_atoi(values[i]);
		free(values[i++]);
		x++;
	}
	free(values);
	return (0);
}

static int	parse_line(t_map *map, int y, int fd)
{
	map->points[y] = (t_point *) malloc(sizeof(t_point) * map->width);
	if (!map->points[y] || parse_every_single_char(map, y, fd))
	{
		while (--y >= 0)
			free(map->points[y]);
		free(map->points);
		return (-1);
	}
	return (0);
}

static int	get_split_count(char *str, char separator)
{
	char	**values;
	int		count;

	count = 0;
	values = ft_split(str, separator);
	if (values)
	{
		while (values[count])
		{
			free(values[count]);
			count++;
		}	
		free(values);
	}
	return (count);
}

static void	init_map_size(t_map *map, char *filename)
{
	int		fd;
	int		width;
	int		height;
	char	*line;

	width = 0;
	height = 0;
	fd = open(filename, O_RDONLY);
	if (fd != -1)
	{
		line = get_next_line(fd);
		if (line)
			width = get_split_count(line, ' ');
		while (line)
		{
			height++;
			free(line);
			line = get_next_line(fd);
		}
		close(fd);
	}
	map->points = NULL;
	map->height = height;
	map->width = width;
}

int	parse_map(t_map *map, char *filename)
{
	int		fd;
	int		y;

	init_map_size(map, filename);
	fd = open(filename, O_RDONLY);
	map->points = (t_point **) malloc (sizeof(t_point *) * map->height);
	if (fd == -1 || !map->points || map->height == 0 || map->width == 0)
	{
		free(map->points);
		if (fd != -1)
			close(fd);
		return (-1);
	}
	y = -1;
	while (++y < map->height)
	{
		if (parse_line(map, y, fd) == -1)
		{
			close(fd);
			return (-1);
		}
	}
	return (close(fd));
}
