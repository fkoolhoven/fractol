/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:47:18 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/03/12 16:58:04 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int	julia_fractal(t_fractol fractol, int x, int y)
{
	double	x_scaled;
	double	y_scaled;
	double	tmp;
	double c_r;
	double c_i;
	
	x_scaled = scale_x_coordinate(fractol, x);
	y_scaled = scale_y_coordinate(fractol, y);
	fractol.iterations = 0;
	fractol.threshold = 4;

	c_r = 0.4;
	c_i = 0.2;

	fractol.iterations = 0;
	while (fractol.iterations < fractol.max_iterations)
	{
		if ((y_scaled * y_scaled + x_scaled * x_scaled) > fractol.threshold)
			break ;
		tmp = 2 * x_scaled * y_scaled + c_i;
		x_scaled = x_scaled * x_scaled - y_scaled * y_scaled + c_r;
		y_scaled = tmp;
		fractol.iterations++;
	}
	return (fractol.iterations);
}
