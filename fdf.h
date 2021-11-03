/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mframbou <mframbou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:24:17 by mframbou          #+#    #+#             */
/*   Updated: 2021/11/03 10:59:29 by mframbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include "./libft/libft.h"
# include "mlx_keycodes.h"

enum e_viewtype
{
	VIEW_ISO,
	VIEW_TOP,
	VIEW_SIDE,
	VIEW_FRONT,
	VIEW_BACK
};

typedef struct s_img_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img_data;

typedef struct s_img
{
	void	*img;
	int		width;
	int		height;
}	t_img;

typedef struct s_point
{
	int	cart_x;
	int	cart_y;
	int	cart_z;
	int	x_2d;
	int	y_2d;
}	t_point;

typedef struct s_window
{
	void	*mlx;
	void	*window;
	int		width;
	int		height;
}	t_window;

typedef struct s_bounding_box
{
	int	left;
	int	right;
	int	top;
	int	bottom;
}	t_bounding_box;

typedef struct s_map
{
	t_point	**points;
	int		width;
	int		height;
}	t_map;

typedef struct s_render
{
	t_window		main_win;
	t_img_data		img;
	t_bounding_box	bbox;
	t_map			map;
	t_point			center_offset;
	float			scale;
	int				viewtype;
	int				color;
	char			rgb_enabled;
}	t_render;

// Rendering
int				do_render(t_render *render);
void			do_render_centered(t_render *render);

// Rendering utils
void			init_iso_and_bounding_box(t_render *render);
void			rotate_cart_left(t_map *map);
void			rotate_cart_right(t_map *map);

// Color utils
int				create_trgb(int t, int r, int g, int b);
int				get_t(int trgb);
int				get_r(int trgb);
int				get_g(int trgb);
int				get_b(int trgb);
int				add_shading(int trgb, double shading);
int				get_opposite(int trgb);
int				get_next_hsl_color(unsigned int color, int shift);

// MLX Utils
void			mlx_put_pixel_img(t_img_data *img, int x, int y, int color);
unsigned int	mlx_get_pixel_img(t_img_data *img, int x, int y);
void			mlx_init_img(t_img_data *img, int width, int height, int color);
void			mlx_put_line_to_img(t_img_data *img, t_point start, t_point end,
					int color);

// Parsing
int				parse_map(t_map *map, char *filename);

// Errors
int				print_error(void);
void			free_map(t_map *map);

// Input management
int				keys_hook(int keycode, t_render *render);

#endif