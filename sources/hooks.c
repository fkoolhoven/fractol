/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:57:25 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/03/14 20:58:39 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static t_fractol	zoom_out(t_fractol f, double temp_width, double temp_heigth)
{
	f.complex_width *= 1.05;
	f.move_horizontal -= (f.complex_width - temp_width) / 2;
	f.complex_heigth *= 1.05;
	f.move_vertical -= (f.complex_heigth - temp_heigth) / 2;
	if (f.max_iterations != 100)
		f.max_iterations--;
	return (f);
}

static t_fractol	zoom_in(t_fractol f, double temp_width, double temp_heigth)
{
	f.complex_width *= 0.95;
	f.move_horizontal += (temp_width - f.complex_width) / 2;
	f.complex_heigth *= 0.95;
	f.move_vertical += (temp_heigth - f.complex_heigth) / 2;
	if (f.complex_width < 4.0)
		f.max_iterations++;
	return (f);
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fractol	*fractol;
	double		temp_width;
	double		temp_heigth;

	fractol = param;
	temp_width = fractol->complex_width;
	temp_heigth = fractol->complex_heigth;
	xdelta = 0;
	if (ydelta > 0)
		*fractol = zoom_in(*fractol, temp_width, temp_heigth);
	else if (ydelta < 0)
		*fractol = zoom_out(*fractol, temp_width, temp_heigth);
	render_image(*fractol);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_fractol	*fractol;

	fractol = param;
	if (keydata.key == MLX_KEY_DOWN)
		fractol->move_vertical += fractol->complex_heigth / 50;
	else if (keydata.key == MLX_KEY_UP)
		fractol->move_vertical -= fractol->complex_heigth / 50;
	else if (keydata.key == MLX_KEY_RIGHT)
		fractol->move_horizontal += fractol->complex_width / 50;
	else if (keydata.key == MLX_KEY_LEFT)
		fractol->move_horizontal -= fractol->complex_width / 50;
	if (keydata.key == MLX_KEY_DOWN || keydata.key == MLX_KEY_UP
		|| keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
		render_image(*fractol);
}

void	loop_hook(void *param)
{
	t_fractol	*fractol;

	fractol = param;
	if (fractol->mlx_ptr->width != fractol->window_width
		|| fractol->mlx_ptr->height != fractol->window_heigth)
	{
		fractol->window_width = fractol->mlx_ptr->width;
		fractol->window_heigth = fractol->mlx_ptr->height;
		fractol->image_width = fractol->window_width;
		fractol->image_heigth = fractol->window_heigth;
		mlx_resize_image(fractol->img_ptr,
			fractol->image_width, fractol->image_heigth);
		render_image(*fractol);
	}
}
