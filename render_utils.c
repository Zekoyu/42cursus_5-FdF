/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:52:40 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/02 14:34:54 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	rotate_cart_left(t_map *map)
{
	int		tmp;
	int		x;
	int		y;
	t_point	*point;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			point = &(map->points[y][x]);
			tmp = point->cart_y;
			point->cart_y = -point->cart_x;
			point->cart_x = tmp;
			x++;
		}
		y++;
	}
}

void	rotate_cart_right(t_map *map)
{
	int		tmp;
	int		x;
	int		y;
	t_point	*point;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			point = &(map->points[y][x]);
			tmp = point->cart_y;
			point->cart_y = point->cart_x;
			point->cart_x = -tmp;
			x++;
		}
		y++;
	}
}

static void	init_iso_coords(t_point *point, float scale, int type)
{
	if (type == VIEW_ISO)
	{
		point->x_2d = (point->cart_x - point->cart_y) * scale;
		point->y_2d = ((float)(point->cart_x + point->cart_y) / 2.0
				- point->cart_z) * scale;
	}
	else if (type == VIEW_TOP)
	{
		point->x_2d = (point->cart_x) * scale;
		point->y_2d = -(point->cart_y) * scale;
	}
	else if (type == VIEW_SIDE)
		point->x_2d = (point->cart_y) * scale;
	else if (type == VIEW_FRONT)
		point->x_2d = (point->cart_x) * scale;
	else if (type == VIEW_BACK)
		point->x_2d = -(point->cart_x) * scale;
	if (type == VIEW_SIDE || type == VIEW_FRONT || type == VIEW_BACK)
		point->y_2d = -(point->cart_z) * scale;
}

static void	init_bounding_box(t_bounding_box *bbox, t_point point)
{
	bbox->left = point.x_2d;
	bbox->right = point.x_2d;
	bbox->top = point.y_2d;
	bbox->bottom = point.y_2d;
}

void	init_iso_and_bounding_box(t_render *render)
{
	int	y;
	int	x;

	init_iso_coords(&(render->map.points[0][0]),
		render->scale, render->viewtype);
	init_bounding_box(&render->bbox, render->map.points[0][0]);
	y = -1;
	while (++y < render->map.height)
	{
		x = -1;
		while (++x < render->map.width)
		{
			init_iso_coords(&(render->map.points[y][x]),
				render->scale, render->viewtype);
			if (render->map.points[y][x].x_2d < render->bbox.left)
				render->bbox.left = render->map.points[y][x].x_2d;
			if (render->map.points[y][x].x_2d > render->bbox.right)
				render->bbox.right = render->map.points[y][x].x_2d;
			if (render->map.points[y][x].y_2d < render->bbox.top)
				render->bbox.top = render->map.points[y][x].y_2d;
			if (render->map.points[y][x].y_2d > render->bbox.bottom)
				render->bbox.bottom = render->map.points[y][x].y_2d;
		}
	}
}
