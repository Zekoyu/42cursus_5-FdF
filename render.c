/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:34:00 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/03 10:48:38 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	translate_img_bbox(t_render *render, int x, int y)
{
	int	i;
	int	j;

	j = 0;
	while (j < render->map.height)
	{
		i = 0;
		while (i < render->map.width)
		{
			render->map.points[j][i].x_2d += x;
			render->map.points[j][i].y_2d += y;
			i++;
		}
		j++;
	}
	render->bbox.right += x;
	render->bbox.left += x;
	render->bbox.bottom += y;
	render->bbox.top += y;
}

static void	draw_map_to_img(t_img_data *img, t_map *map, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width - 1)
		{
			mlx_put_line_to_img(img, map->points[y][x],
				map->points[y][x + 1], color);
			x++;
		}
		y++;
	}
	x = 0;
	while (x < map->width)
	{
		y = -1;
		while (++y < map->height - 1)
			mlx_put_line_to_img(img, map->points[y][x],
				map->points[y + 1][x], color);
		x++;
	}
}

int	do_render(t_render *render)
{
	mlx_clear_window(render->main_win.mlx, render->main_win.window);
	mlx_destroy_image(render->main_win.mlx, render->img.img);
	init_iso_and_bounding_box(render);
	render->img.img = mlx_new_image(render->main_win.mlx,
			(render->bbox.right - render->bbox.left) + 1,
			(render->bbox.bottom - render->bbox.top) + 1);
	render->img.addr = mlx_get_data_addr(render->img.img,
			&render->img.bits_per_pixel,
			&render->img.line_length, &render->img.endian);
	translate_img_bbox(render, -render->bbox.left, -render->bbox.top);
	if (render->rgb_enabled)
		render->color = get_next_hsl_color(render->color, 20);
	draw_map_to_img(&render->img, &render->map, render->color);
	mlx_put_image_to_window(render->main_win.mlx, render->main_win.window,
		render->img.img, render->center_offset.x_2d,
		render->center_offset.y_2d);
	return (1);
}

void	do_render_centered(t_render *render)
{
	mlx_clear_window(render->main_win.mlx, render->main_win.window);
	mlx_destroy_image(render->main_win.mlx, render->img.img);
	init_iso_and_bounding_box(render);
	render->img.img = mlx_new_image(render->main_win.mlx,
			(render->bbox.right - render->bbox.left) + 1,
			(render->bbox.bottom - render->bbox.top) + 1);
	render->img.addr = mlx_get_data_addr(render->img.img,
			&render->img.bits_per_pixel,
			&render->img.line_length, &render->img.endian);
	translate_img_bbox(render, -render->bbox.left, -render->bbox.top);
	draw_map_to_img(&render->img, &render->map, render->color);
	render->center_offset.x_2d = (render->main_win.width / 2)
		- (render->bbox.left + render->bbox.right) / 2;
	render->center_offset.y_2d = (render->main_win.height / 2)
		- (render->bbox.top + render->bbox.bottom) / 2;
	mlx_put_image_to_window(render->main_win.mlx, render->main_win.window,
		render->img.img, render->center_offset.x_2d,
		render->center_offset.y_2d);
}
