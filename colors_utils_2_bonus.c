/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils_2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:07:35 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/02 18:31:43 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	add_shading(int trgb, double shading)
{
	if (shading < 0)
		shading = 0;
	else if (shading > 1)
		shading = 1;
	return (create_trgb(
			get_t(trgb),
			get_r(trgb) * (1 - shading),
			get_g(trgb) * (1 - shading),
			get_b(trgb) * (1 - shading)));
}

// Invert all bits then set the first 3 bytes back to 0 (only keep data byte)
int	get_opposite(int trgb)
{
	return (create_trgb(
			get_t(trgb),
			~get_r(trgb) & 0x000000FF,
			~get_g(trgb) & 0x000000FF,
			~get_b(trgb) & 0x000000FF));
}

// Separate function for get_next_hsl
// Just shift the color by 1 in the circle
static int	shift_color(int c)
{
	if (get_r(c) == 0xFF && get_g(c) != 0xFF)
	{
		if (get_b(c) == 0x00 && get_g(c) != 0xFF)
			return (create_trgb(get_t(c), get_r(c), get_g(c) + 1, get_b(c)));
		else if (get_g(c) != 0xFF)
			return (create_trgb(get_t(c), get_r(c), get_g(c), get_b(c) - 1));
	}
	if (get_g(c) == 0xFF && get_b(c) != 0xFF)
	{
		if (get_r(c) != 0x00 && get_b(c) != 0xFF)
			return (create_trgb(get_t(c), get_r(c) - 1, get_g(c), get_b(c)));
		else if (get_b(c) != 0xFF)
			return (create_trgb(get_t(c), get_r(c), get_g(c), get_b(c) + 1));
	}
	if (get_b(c) == 0xFF)
	{
		if (get_g(c) != 0x00 && get_r(c) != 0xFF)
			return (create_trgb(get_t(c), get_r(c), get_g(c) - 1, get_b(c)));
		else if (get_r(c) != 0xFF)
			return (create_trgb(get_t(c), get_r(c) + 1, get_g(c), get_b(c)));
	}
	return (c);
}

// Loop through RGB Spectrum
int	get_next_hsl_color(unsigned int color, int shift)
{
	int	i;

	i = 0;
	while (i < shift)
	{
		color = shift_color(color);
		i++;
	}
	return (color);
}
