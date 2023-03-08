/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:47:18 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/03/08 16:49:14 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

    // f(z) = z^2 + c 
    // c is a constant complex number (paramater that should be passed on command line)
    // check how many iterates it takes to pass threshold
    // if f(z) remains bounded -> part of julia set

int	julia_fractal(t_fractol fractol, int x, int y)
{
	double	x_scaled;
	double	y_scaled;
	double	real;
	double	imaginary;
	//double	temp;
	double c;

	x_scaled = scale_x_coordinate(fractol, x);
	y_scaled = scale_y_coordinate(fractol, y);
	c = 0.282 - 0.58;
	real = 0.0;
	imaginary = 0.0;
	fractol.iterations = 0;
	fractol.threshold = 4;
	while ((real * real + imaginary * imaginary) < fractol.threshold
		&& fractol.iterations < fractol.max_iterations)
	{
		real = x_scaled;
		imaginary = y_scaled;
	    x_scaled = real * real - imaginary * imaginary + (c * y_scaled);
      	y_scaled = 2 * real * imaginary + (c * x_scaled);
		//printf("temp = %f\n", temp);
		if((x_scaled * x_scaled + y_scaled * y_scaled) > 4)
			return (fractol.iterations);
		fractol.iterations++;
	}

	// double c = 0.282 - 0.58 * y_scaled;
	// real = 0.0;
	// imaginary = 0.0;
	// fractol.iterations = 0;
	// fractol.threshold = 4;
	// while ((real * real + imaginary * imaginary) < fractol.threshold
	// 	&& fractol.iterations < fractol.max_iterations)
	// {
	// 	temp = x_scaled * x_scaled - y_scaled * y_scaled;
	// 	y_scaled = 2 * x_scaled * y_scaled + (c * y);
	// 	x_scaled = temp + (c * x);
	// 	//printf("temp = %f\n", temp);
	// 	fractol.iterations++;
	// }
	return (fractol.iterations);
}
