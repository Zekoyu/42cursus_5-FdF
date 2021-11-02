/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 10:27:15 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/02 18:29:45 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* 	Top and bottom inversed
 	Y axis going down
 	X axis going right

	     x
	+-------->
	|
  y	|
	|
	V
*/
void	init_main_win(t_window *main_win, int width, int height, char *name)
{
	main_win->mlx = mlx_init();
	main_win->width = width;
	main_win->height = height;
	main_win->window = mlx_new_window(main_win->mlx,
			main_win->width, main_win->height, name);
}

static float	get_fullscreen_scale(t_bounding_box *bbox,
		int width, int height)
{
	return ((float) fabs(fmin((double) fabs((double) width - 100.0)
				/ (bbox->right - bbox->left),
				(double) fabs((double) height - 100.0)
				/ (bbox->bottom - bbox->top))));
}

int	main(int argc, char *argv[])
{
	t_render		render;

	if (argc < 2 || parse_map(&render.map, argv[1]) == -1)
		return (print_error());
	render.viewtype = VIEW_ISO;
	render.color = 0x00FF0000;
	render.scale = 1.0;
	init_main_win(&render.main_win, 1920, 1080, "Orondarnaque");
	init_iso_and_bounding_box(&render);
	render.img.img = mlx_new_image(render.main_win.mlx,
			(render.bbox.right - render.bbox.left) + 1,
			(render.bbox.bottom - render.bbox.top) + 1);
	render.img.addr = mlx_get_data_addr(render.img.img,
			&render.img.bits_per_pixel, &render.img.line_length,
			&render.img.endian);
	render.scale = get_fullscreen_scale(&render.bbox,
			render.main_win.width, render.main_win.height);
	do_render_centered(&render);
	mlx_key_hook(render.main_win.window, &keys_hook, &render);
	mlx_loop_hook(render.main_win.mlx, &do_render, &render);
	mlx_loop(render.main_win.mlx);
	mlx_destroy_image(render.main_win.mlx, render.img.img);
	mlx_destroy_window(render.main_win.mlx, render.main_win.window);
}
