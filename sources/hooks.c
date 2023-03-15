/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:57:25 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/03/15 15:02:53 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static t_fractol	zoom_out(t_fractol f, double temp_width, double temp_height)
{
	f.complex_width *= 1.05;
	f.move_horizontal -= (f.complex_width - temp_width) / 2;
	f.complex_height *= 1.05;
	f.move_vertical -= (f.complex_height - temp_height) / 2;
	if (f.max_iterations != 100)
		f.max_iterations--;
	return (f);
}

static t_fractol	zoom_in(t_fractol f, double temp_width, double temp_height)
{
	f.complex_width *= 0.95;
	f.move_horizontal += (temp_width - f.complex_width) / 2;
	f.complex_height *= 0.95;
	f.move_vertical += (temp_height - f.complex_height) / 2;
	if (f.complex_width < 4.0)
		f.max_iterations++;
	return (f);
}

void	mouse_scroll(double xdelta, double ydelta, void *param)
{
	t_fractol	*f;

	f = param;
	xdelta = 0;
	if (ydelta > 0)
		*f = zoom_in(*f, f->complex_width, f->complex_height);
	else if (ydelta < 0)
		*f = zoom_out(*f, f->complex_width, f->complex_height);
	render_image(*f);
}

void	key_press(mlx_key_data_t keydata, void *param)
{
	t_fractol	*fractol;

	fractol = param;
	if (keydata.key == MLX_KEY_DOWN)
		fractol->move_vertical += fractol->complex_height / 50;
	else if (keydata.key == MLX_KEY_UP)
		fractol->move_vertical -= fractol->complex_height / 50;
	else if (keydata.key == MLX_KEY_RIGHT)
		fractol->move_horizontal += fractol->complex_width / 50;
	else if (keydata.key == MLX_KEY_LEFT)
		fractol->move_horizontal -= fractol->complex_width / 50;
	if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_UP
		|| keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
		render_image(*fractol);
}

void	resize_window(int32_t width, int32_t height, void *param)
{
	t_fractol	*fractol;

	fractol = param;
	fractol->window_width = width;
	fractol->window_height = height;
	fractol->image_width = width;
	fractol->image_height = height;
	mlx_resize_image(fractol->img_ptr, width, height);
	render_image(*fractol);
}
