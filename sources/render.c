/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:17:11 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/03/03 23:04:51 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static unsigned int	get_pixel_depth(t_fractol *fractol, int x, int y)
{
	int				iterations;
	unsigned int	color;

	iterations = 0;
	if (fractol->mandelbrot == 1)
		iterations = mandelbrot_fractal(fractol, x, y);
	else if (fractol->julia == 1)
		iterations = julia_fractal(fractol, x, y);
	color = get_color(fractol, iterations, x, y);
	return (color);
}

void	render_image(t_fractol *fractol)
{
	unsigned int	color;
	int				x;
	int				y;

	x = 0;
	y = 0;
	while (y < fractol->image_height)
	{
		while (x < fractol->image_width)
		{
			color = get_pixel_depth(fractol, x, y);
			mlx_put_pixel(fractol->img_ptr, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_image_to_window(fractol->mlx_ptr, fractol->img_ptr, 0, 0);
}
