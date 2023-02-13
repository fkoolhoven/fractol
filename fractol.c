/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:42:19 by felicia           #+#    #+#             */
/*   Updated: 2023/02/10 23:19:25 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

static void	set_pixel_color(t_fractol *fractol, int x, int y, int color)
{
	int	first_byte;

	first_byte = x * 4 + y * fractol->image_width * 4;
	fractol->buf[first_byte] = color;
	fractol->buf[first_byte + 1] = color >> 8;
	fractol->buf[first_byte + 2] = color >> 16;
	fractol->buf[first_byte + 3] = color >> 24;
}

int		get_color(int iterations)
{
	if (iterations >= 0 && iterations <= 10)
		return (0xEC9531);
	else if (iterations >= 11 && iterations <= 20)
		return (0xFAD96A);
	else if (iterations >= 21 && iterations <= 30)
		return (0xF5BABA);
	else if (iterations >= 31 && iterations <= 40)
		return (0xCCFFFF);
	else if (iterations >= 41 && iterations <= 50)
		return (0x1687B7);
	else if (iterations >= 51 && iterations <= 60)
		return (0xFF5FAA);
	else if (iterations >= 61 && iterations <= 70)
		return (0xFF5FAA);
	else if (iterations >= 71 && iterations <= 80)
		return (0x000000);
	return (0xFFFFFF);
}

int	mandelbrot(t_fractol fractol, int x, int y)
{
	double	real_a;
	double	imaginary_b;
	int		iterations;
	double	z_real;
	double	z_imaginary;
	double	tmp;


	real_a 		= fractol.move_horizontal + (x - fractol.image_width/fractol.complex_heigth)*fractol.complex_width/fractol.image_width;
	imaginary_b = fractol.move_vertical + (y - fractol.image_heigth/fractol.complex_heigth)*fractol.complex_width/fractol.image_width;
	z_real = 0;
	z_imaginary = 0;
	iterations = 0;
	fractol.max_iterations = 80;
	while (iterations < fractol.max_iterations)
	{
		if ((z_real * z_real + z_imaginary * z_imaginary) > 4.0)
			return (iterations);
		tmp = 2 * z_real * z_imaginary + imaginary_b;
		z_real = z_real * z_real - z_imaginary * z_imaginary + real_a;
		z_imaginary = tmp;
		iterations++;
	}
	return (iterations);
}

void	render_image(t_fractol fractol)
{
	int	color;
	int	iterations = 0;
	int	x = 0;
	int	y = 0;

	if (fractol.img_ptr != NULL)
	 	mlx_destroy_image(fractol.mlx_ptr, fractol.img_ptr); 
	fractol.img_ptr = mlx_new_image(fractol.mlx_ptr, fractol.image_width, fractol.image_heigth);
	fractol.buf = mlx_get_data_addr(fractol.img_ptr, &fractol.bits_per_pixel, &fractol.size_len, &fractol.endian);
	
	while (y < fractol.image_heigth)
	{
		while (x < fractol.image_width)
		{
			iterations = mandelbrot(fractol, x, y);
			color = get_color(iterations);
			set_pixel_color(&fractol, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(fractol.mlx_ptr, fractol.win_ptr, fractol.img_ptr, 0, 0);
}

int	zoom(int key, t_fractol *fractol)
{
	if (key == 0x7D) // down
	{
		fractol->move_vertical = fractol->move_vertical + (fractol->complex_heigth / 50);
	}
	else if (key == 0x7E) // up
	{
		fractol->move_vertical = fractol->move_vertical - (fractol->complex_heigth / 50);
	}
	else if (key == 0x7C) // right
	{
		fractol->move_horizontal = fractol->move_horizontal + (fractol->complex_width / 50);
	}
	else if (key == 0x7B) // left
	{
		fractol->move_horizontal = fractol->move_horizontal - (fractol->complex_width / 50);
	}
	else if (key == 49) // zoom in spacebar
	{	
		fractol->complex_width = fractol->complex_width * 0.95;
		fractol->complex_heigth = fractol->complex_heigth * 0.95;
	}
	render_image(*fractol);
	return (0);
}

void	fill_window(t_fractol fractol)
{
	int	full = fractol.window_width * fractol.window_heigth;
	int	w = 0;
	int	h = 0;
	int	f = 0;

	while (h < fractol.window_heigth)
	{
		while (w < fractol.window_width && f < full)
		{
			mlx_pixel_put(fractol.mlx_ptr, fractol.win_ptr, w, h, 0xA33216);
			f++;
			w++;
		}
		w = 0;
		h++;
	}
}

int main(void)
{
	t_fractol	fractol;
	char		*buf;
	int			hook;

	// paramater setup, create function for?
	fractol.window_width = 1000;
	fractol.window_heigth = 700;
	fractol.image_width = 900;
	fractol.image_heigth = 700;
	fractol.complex_width = 4.0;
	fractol.complex_heigth = 2.0;
	fractol.move_horizontal = 0.0;
	fractol.move_vertical = 0.0;
	fractol.img_ptr = NULL;

	// basic mlx and window setup
	fractol.mlx_ptr = mlx_init();
	if (fractol.mlx_ptr == NULL)
	    fprintf(stderr, "could not initialize connection between software and display\n");
	fractol.win_ptr = mlx_new_window(fractol.mlx_ptr, fractol.window_width, fractol.window_heigth, "fractol");
	if (fractol.win_ptr == NULL)
	    fprintf(stderr, "could not create new window\n");

	// basic graphic setup
	fill_window(fractol);
	render_image(fractol);

	// event setup and handling
	hook = mlx_key_hook(fractol.win_ptr, zoom, &fractol);
	mlx_loop(fractol.mlx_ptr);

	return (0);
}