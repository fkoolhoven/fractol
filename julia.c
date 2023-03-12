/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 15:47:18 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/03/12 18:01:05 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

double	ft_atof(char *str)
{
	double	number;
	int		negative;
	int		i;
	double	div;

	number = 0;
	negative = 1;
	div = 0.1;
	i = 0;
	if (str[i] == '-')
	{
		negative = -1;
		i++;
	}
	while (str[i] && ft_isdigit(str[i]) && str[i] != '.')
	{
		number = (number * 10.0) + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		number = number + ((str[i] - '0') * div);
		div *= 0.1;
		i++;
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (-42);
	return (number * negative);
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
