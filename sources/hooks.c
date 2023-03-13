/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:57:25 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/03/13 13:13:54 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

t_fractol	zoom_out(t_fractol fractol, double temp_width, double temp_heigth)
{
	fractol.complex_width *= 1.05;
	fractol.move_horizontal -= (fractol.complex_width - temp_width) / 2;
	fractol.complex_heigth *= 1.05;
	fractol.move_vertical -= (fractol.complex_heigth - temp_heigth) / 2;
	if (fractol.max_iterations != 100)
		fractol.max_iterations--;
	return (fractol);
}

t_fractol	zoom_in(t_fractol fractol, double temp_width, double temp_heigth)
{
	fractol.complex_width *= 0.95;
	fractol.move_horizontal += (temp_width - fractol.complex_width) / 2;
	fractol.complex_heigth *= 0.95;
	fractol.move_vertical += (temp_heigth - fractol.complex_heigth) / 2;
	if (fractol.complex_width < 4.0)
		fractol.max_iterations++;
	return (fractol);
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

void	resize_window(int32_t width, int32_t height, void *param)
{
	t_fractol	*fractol;

	fractol = param;
	fractol->image_width = width;
	fractol->image_heigth = height;
	fractol->img_ptr = mlx_new_image(fractol->mlx_ptr, fractol->image_width,
			fractol->image_heigth);
	render_image(*fractol);
}
