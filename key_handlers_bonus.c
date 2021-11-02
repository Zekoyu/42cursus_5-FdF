/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_handlers_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 18:14:42 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/02 18:31:23 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	if_forest_view_keycode(int keycode, t_render *render)
{
	if (keycode == KEY_1)
		render->viewtype = VIEW_ISO;
	else if (keycode == KEY_2)
		render->viewtype = VIEW_TOP;
	else if (keycode == KEY_3)
		render->viewtype = VIEW_SIDE;
	else if (keycode == KEY_4)
		render->viewtype = VIEW_FRONT;
	else if (keycode == KEY_5)
		render->viewtype = VIEW_BACK;
}

static void	if_forest_keycode(int keycode, t_render *render)
{
	if (keycode == KEY_PLUS)
		render->scale += 1;
	else if (keycode == KEY_MINUS)
	{
		render->scale -= 1;
		if (render->scale < 0.5)
			render->scale = 0.5;
	}
	else if (keycode == KEY_Q)
		rotate_cart_left(&render->map);
	else if (keycode == KEY_E)
		rotate_cart_right(&render->map);
	else if (keycode == KEY_A)
		render->center_offset.x_2d += 50;
	else if (keycode == KEY_D)
		render->center_offset.x_2d -= 50;
	else if (keycode == KEY_W)
		render->center_offset.y_2d += 50;
	else if (keycode == KEY_S)
		render->center_offset.y_2d -= 50;
	if_forest_view_keycode(keycode, render);
}

int	keys_hook(int keycode, t_render *render)
{
	if_forest_keycode(keycode, render);
	if (keycode == KEY_ESC)
	{
		mlx_destroy_image(render->main_win.mlx, render->img.img);
		mlx_destroy_window(render->main_win.mlx, render->main_win.window);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS
		|| keycode == KEY_W || keycode == KEY_A
		|| keycode == KEY_S || keycode == KEY_D
		|| keycode == KEY_Q || keycode == KEY_E)
		do_render(render);
	else if (keycode == KEY_1 || keycode == KEY_2 || keycode == KEY_3
		|| keycode == KEY_4 || keycode == KEY_5)
		do_render_centered(render);
	return (1);
}
