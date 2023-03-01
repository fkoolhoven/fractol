/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:58:24 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/03/01 12:10:55 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void    set_pixel_color(t_fractol *fractol, int x, int y, int color)
{
	int	first_byte;

	first_byte = x * 4 + y * fractol->image_width * 4;
	fractol->img_ptr->pixels[first_byte + 0] = color >> 24;
	fractol->img_ptr->pixels[first_byte + 1] = color >> 16;
	fractol->img_ptr->pixels[first_byte + 2] = color >> 8;
	fractol->img_ptr->pixels[first_byte + 3] = color;
}

int	interpolate_color(int first, int second, double amount)
{
	int	result;
	int	difference;

	difference = second - first;

	result = first + (difference * amount);
	return (result); 
}

double	normalize_iterations(t_color c, int iterations, int x, int y)
{
	double 	normalized;
    double 	log_zn = log(x * x + y * y) / 2;
	double 	nu = log(log_zn / log(2)) / log(2);

    normalized = iterations + 1 - nu + 2;
	normalized = (normalized - c.range_start) / c.range;
	return (normalized);
}

int	get_color(t_fractol fractol, t_color c, int iterations, int x, int y)
{
	unsigned int	color_as_int;
	double			normalized;

	if (iterations == fractol.max_iterations)
		return (255);
	normalized = normalize_iterations(c, iterations, x, y);

	unsigned int	channel_one = interpolate_color(*c.first[0], *c.second[0], normalized);
	unsigned int	channel_two = interpolate_color(*c.first[1], *c.second[1], normalized);
	unsigned int	channel_three = interpolate_color(*c.first[2], *c.second[2], normalized);
	unsigned int	channel_four = 0xFF;

	color_as_int = (channel_one << 24) + (channel_two << 16) + (channel_three << 8) + channel_four;
	return (color_as_int);
}