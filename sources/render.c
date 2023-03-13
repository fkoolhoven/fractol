/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 14:17:11 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/03/13 18:27:30 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void	render_image(t_fractol fractol)
{
	unsigned int	color;
	unsigned int	iterations;
	int				x;
	int				y;

	iterations = 0;
	x = 0;
	y = 0;
	while (y <= fractol.image_heigth)
	{
		while (x <= fractol.image_width)
		{
			if (fractol.mandelbrot == 1)
				iterations = mandelbrot_fractal(fractol, x, y);
			else if (fractol.julia == 1)
				iterations = julia_fractal(fractol, x, y);
			if (iterations == fractol.max_iterations)
				color = 0x000000FF;
			else
			{
				fractol.palette = get_palette(fractol, iterations);
				color = get_color(fractol.palette, iterations, x, y);
			}
			set_pixel_color(&fractol, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_image_to_window(fractol.mlx_ptr, fractol.img_ptr, 0, 0);
}
