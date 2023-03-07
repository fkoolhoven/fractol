/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:58:24 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/03/07 16:44:53 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	set_pixel_color(t_fractol *fractol, int x, int y, int color)
{
	int	first_byte;

	first_byte = x * 4 + y * fractol->image_width * 4;
	fractol->img_ptr->pixels[first_byte + 0] = color >> 24;
	fractol->img_ptr->pixels[first_byte + 1] = color >> 16;
	fractol->img_ptr->pixels[first_byte + 2] = color >> 8;
	fractol->img_ptr->pixels[first_byte + 3] = color;
}

// void	free_palette(t_color c)
// {
// 	int	i;

// 	i = 0;
// 	while (i <= 3)
// 	{
// 		free(c.first[i]);
// 		free(c.second[i]);
// 		i++;
// 	}
// }

int	interpolate_color(int first_color, int second_color, float amount)
{
	int	result;

	result = first_color + (second_color - first_color) * amount;
	return (result);
}

float	normalize_iterations(t_color c, int iterations, int x, int y)
{
	float	amount;
	float	current_log;

	current_log = log(x * x + y * y) / 2;
	amount = iterations - (log((current_log) / log(2)) / log(2)) + 3;
	amount = (amount - c.range_start) / c.range;
	return (amount);
}

int	get_color(t_color c, int iterations, int x, int y)
{
	unsigned int	color;
	float			amount;

	amount = normalize_iterations(c, iterations, x, y);
	color = interpolate_color(*c.first[0], *c.second[0], amount) << 24;
	color += interpolate_color(*c.first[1], *c.second[1], amount) << 16;
	color += interpolate_color(*c.first[2], *c.second[2], amount) << 8;
	color += 0xFF;
	//free_palette(c);
	return (color);
}
