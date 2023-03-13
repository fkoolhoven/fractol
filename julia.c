/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:47:18 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/03/13 10:37:43 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

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
