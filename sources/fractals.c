/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 12:28:49 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/03/13 18:27:27 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

// real_a 	v  = fractol.move_horizontal + (x - fractol.image_width  / fractol.complex_heigth ) * fractol.complex_width / fractol.image_width;
// imaginary_b = fractol.move_vertical   + (y - fractol.image_heigth / fractol.complex_heigth ) * fractol.complex_width / fractol.image_width;
//	0 + (0 - 300 / 2) * 4 / 400


static double	scale_y_coordinate(t_fractol fractol, int y)
{
	double	y_scaled;

	y_scaled = y - fractol.image_heigth / fractol.complex_heigth; // 300 / 3
	y_scaled *= fractol.complex_width / fractol.image_width; // 4 / 400
	y_scaled += fractol.move_vertical;
	y_scaled *= -1;
	return (y_scaled);
}

static double	scale_x_coordinate(t_fractol fractol, int x)
{
	double	x_scaled;

	x_scaled = x - fractol.image_width / fractol.complex_heigth;
	x_scaled *= fractol.complex_width / fractol.image_width;
	x_scaled += fractol.move_horizontal;
	return (x_scaled);
}

int	julia_fractal(t_fractol fractol, int x, int y)
{
	double	x_scaled;
	double	y_scaled;
	double	temp;

	x_scaled = scale_x_coordinate(fractol, x);
	y_scaled = scale_y_coordinate(fractol, y);
	fractol.iterations = 0;
	fractol.threshold = 4;
	fractol.iterations = 0;
	while ((y_scaled * y_scaled + x_scaled * x_scaled) < fractol.threshold
		&& fractol.iterations < fractol.max_iterations)
	{
		temp = 2 * x_scaled * y_scaled + fractol.c_imaginary;
		x_scaled = x_scaled * x_scaled - y_scaled * y_scaled + fractol.c_real;
		y_scaled = temp;
		fractol.iterations++;
	}
	return (fractol.iterations);
}

int	mandelbrot_fractal(t_fractol fractol, int x, int y)
{
	double	x_scaled;
	double	y_scaled;
	double	real;
	double	imaginary;
	double	temp;

	x_scaled = scale_x_coordinate(fractol, x);
	y_scaled = scale_y_coordinate(fractol, y);
	real = 0.0;
	imaginary = 0.0;
	fractol.iterations = 0;
	fractol.threshold = 4;
	while ((real * real + imaginary * imaginary) < fractol.threshold
		&& fractol.iterations < fractol.max_iterations)
	{
		temp = 2 * real * imaginary + y_scaled;
		real = real * real - imaginary * imaginary + x_scaled;
		imaginary = temp;
		fractol.iterations++;
	}
	return (fractol.iterations);
}
