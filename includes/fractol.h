/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:12:08 by felicia           #+#    #+#             */
/*   Updated: 2023/03/13 12:26:21 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
# include "MLX42.h"
# include <stdio.h>
# include <math.h>

// =====STRUCTS=================================================================

typedef struct s_color
{
	int			***converted_palette;
	int			**second;
	int			**first;
	int			range;
	int			range_start;
	int			modulo;
}	t_color;

typedef struct s_fractol
{
	int			mandelbrot;
	int			julia;
	double		c_real;
	double		c_imaginary;
	int			iterations;
	mlx_t		*mlx_ptr;
	mlx_image_t	*img_ptr;
	int			window_width;
	int			window_heigth;
	int			image_width;
	int			image_heigth;
	double		complex_width;
	double		complex_heigth;
	double		move_vertical;
	double		move_horizontal;
	int			max_iterations;
	int			threshold;
	int			function_result;
	float		zoom;
	int			range;
	int			division;
	t_color		palette;
}	t_fractol;

// =====FUNCTIONS===============================================================

t_fractol	set_parameters_mandelbrot(int argc);
t_fractol	set_parameters_julia(int argc, char **argv);
double		ft_atof(char *str);
int			mandelbrot_fractal(t_fractol fractol, int x, int y);
int			julia_fractal(t_fractol fractol, int x, int y);
double		scale_x_coordinate(t_fractol fractol, int x);
double		scale_y_coordinate(t_fractol fractol, int y);
int			***convert_colors_to_rgb_arrays(void);
void		scroll_hook(double xdelta, double ydelta, void *param);
void		key_hook(mlx_key_data_t keydata, void *param);
void		resize_window(int32_t width, int32_t height, void *param);
t_color		get_palette(t_fractol fractol, int iterations);
int			get_color(t_color c, int iterations, int x, int y);
void		set_pixel_color(t_fractol *fractol, int x, int y, int color);
void		render_image(t_fractol fractol);

#endif