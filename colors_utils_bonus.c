/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:07:35 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/02 18:31:40 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	create_trgb(int t, int r, int g, int b)
{
	if (t < 0)
		t = 0;
	else if (t > 255)
		t = 255;
	if (r < 0)
		r = 0;
	else if (r > 255)
		r = 255;
	if (g < 0)
		g = 0;
	else if (g > 255)
		g = 255;
	if (b < 0)
		b = 0;
	else if (b > 255)
		b = 255;
	return (t << 24 | r << 16 | g << 8 | b);
}

int	get_t(int trgb)
{
	return (trgb >> 24 & 0b11111111);
}

int	get_r(int trgb)
{
	return (trgb >> 16 & 0xFF);
}

int	get_g(int trgb)
{
	return (trgb >> 8 & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}
