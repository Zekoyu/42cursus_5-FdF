/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 12:01:00 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/01 16:13:25 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	mlx_put_line_to_img(t_img_data *img,
	t_point start, t_point end, int color)
{
	float		delta_x;
	float		delta_y;
	int			pixels_count;
	float		pixel_x;
	float		pixel_y;

	delta_x = end.x_2d - start.x_2d;
	delta_y = end.y_2d - start.y_2d;
	pixels_count = (int) sqrtl(delta_x * delta_x + delta_y * delta_y);
	delta_x = delta_x / (float) pixels_count;
	delta_y = delta_y / (float) pixels_count;
	pixel_x = start.x_2d;
	pixel_y = start.y_2d;
	while (pixels_count)
	{
		mlx_put_pixel_img(img, (int) lround(pixel_x),
			(int) lround(pixel_y), color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		pixels_count--;
	}
}

void	mlx_put_pixel_img(t_img_data *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	if (get_t(color) != 0xFF)
		*((unsigned int *) dst) = color;
}

unsigned int	mlx_get_pixel_img(t_img_data *img, int x, int y)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

void	mlx_init_img(t_img_data *img, int width, int height, int color)
{
	int		x;
	int		y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			mlx_put_pixel_img(img, x, y, color);
			x++;
		}
		y++;
	}
}
