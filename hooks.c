/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:57:25 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/03/01 12:02:59 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fractol	*fractol = param;
	double		temp_width = fractol->complex_width;
	double		temp_heigth = fractol->complex_heigth;

	xdelta++;
	if (ydelta > 0)
	{
		fractol->complex_width = fractol->complex_width * 0.95;
		fractol->move_horizontal = fractol->move_horizontal + ((temp_width - fractol->complex_width) / 2);
		fractol->complex_heigth = fractol->complex_heigth * 0.95;
		fractol->move_vertical = fractol->move_vertical + ((temp_heigth - fractol->complex_heigth) / 2);
		if (fractol->complex_width < 4.0)
			fractol->max_iterations++;
	
	}
	else if (ydelta < 0)
	{
		fractol->complex_width = fractol->complex_width * 1.05;
		fractol->move_horizontal = fractol->move_horizontal - ((fractol->complex_width - temp_width) / 2);
		fractol->complex_heigth = fractol->complex_heigth * 1.05;
		fractol->move_vertical = fractol->move_vertical - ((fractol->complex_heigth - temp_heigth) / 2);
		if (fractol->max_iterations != 50)
			fractol->max_iterations--;
	}
	render_image(*fractol);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	
	t_fractol	*fractol = param;

	if (keydata.key == MLX_KEY_DOWN)
		fractol->move_vertical = fractol->move_vertical + (fractol->complex_heigth / 50);
	else if (keydata.key == MLX_KEY_UP)
		fractol->move_vertical = fractol->move_vertical - (fractol->complex_heigth / 50);
	else if (keydata.key == MLX_KEY_RIGHT)
		fractol->move_horizontal = fractol->move_horizontal + (fractol->complex_width / 50);
	else if (keydata.key == MLX_KEY_LEFT)
		fractol->move_horizontal = fractol->move_horizontal - (fractol->complex_width / 50);
	render_image(*fractol);
}

void resize_window(int32_t width, int32_t height, void* param)
{
	t_fractol	*fractol = param;

	fractol->image_width = width;
	fractol->image_heigth = height;
	render_image(*fractol);
}