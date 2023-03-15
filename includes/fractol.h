/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:12:08 by felicia           #+#    #+#             */
/*   Updated: 2023/03/15 13:08:06 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "MLX42.h"
# include <stdio.h>
# include <math.h>

// =====STRUCTS=================================================================

typedef struct s_palette
{
	int	***converted;
	int	**second;
	int	**first;
	int	range;
	int	range_start;
}	t_palette;

typedef struct s_fractol
{
	int				mandelbrot;
	int				julia;
	double			c_real;
	double			c_imaginary;
	int				iterations;
	mlx_t			*mlx_ptr;
	mlx_image_t		*img_ptr;
	int				window_width;
	int				window_height;
	int				image_width;
	int				image_height;
	double			complex_width;
	double			complex_height;
	double			move_horizontal;
	double			move_vertical;
	int				max_iterations;
	int				threshold;
	float			zoom;
	t_palette		palette;
}	t_fractol;

// =====FUNCTIONS===============================================================

t_fractol	set_parameters_mandelbrot(int argc);
t_fractol	set_parameters_julia(int argc, char **argv);
void		render_image(t_fractol fractol);
int			mandelbrot_fractal(t_fractol fractol, int x, int y);
int			julia_fractal(t_fractol fractol, int x, int y);
int			***convert_colors_to_rgb_arrays(void);
void		mouse_scroll(double xdelta, double ydelta, void *param);
void		key_press(mlx_key_data_t keydata, void *param);
t_palette	get_palette(t_fractol fractol, int iterations);
int			get_color(t_palette c, int iterations, int x, int y);
void		resize_window(int32_t width, int32_t height, void *param);
void		free_palette(int ***palette);
t_palette	get_color_range(t_fractol f, int iterations);

#endif