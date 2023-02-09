/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:42:19 by felicia           #+#    #+#             */
/*   Updated: 2023/02/09 20:50:08 by felicia          ###   ########.fr       */
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

int		get_color(int mandelbrot_check)
{
	if (mandelbrot_check == 0)
		return(0x9999FF);
	else if (mandelbrot_check == 1)
		return(0xFFFFFF);
	return (0x000000);
}

int	mandelbrot(t_fractol fractol, int x, int y)
{
	double	real_a;
	double	imaginary_b;
	int		iterations;
	double	zr;
	double	zi;
	double	tmp;

	real_a 		= (x - fractol.image_width/2.0)*4.0/fractol.image_width;
	imaginary_b = (y - fractol.image_heigth/2.0)*4.0/fractol.image_width;
	zr = 0;
	zi = 0;
	iterations = 0;
	fractol.max_iterations = 60;
	while (iterations < fractol.max_iterations)
	{
		if ((zr * zr + zi * zi) > 4.0)
			return (0);
		tmp = 2 * zr * zi + imaginary_b;
		zr = zr * zr - zi * zi + real_a;
		zi = tmp;
		iterations++;
	}
	return (1);
}

void	render_image(t_fractol fractol)
{
	int	color;
	int	mandelbrot_check = 0;
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
			mandelbrot_check = mandelbrot(fractol, x, y);
			color = get_color(mandelbrot_check);
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
	if (key == 126)
	{	
		fractol->image_width = fractol->image_width + 10;
		fractol->image_heigth = fractol->image_heigth + 10;
		render_image(*fractol);
	}
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
	fractol.image_width = 300;
	fractol.image_heigth = 200;
	fractol.window_width = 1000;
	fractol.window_heigth = 1000;
	fractol.img_ptr = NULL;

	// mlx_string_put(fractol.mlx_ptr, fractol.win_ptr, 1100, 650, 0xFF00FF, "purple"); // 12079 int is 32 bits
	// mlx_string_put(fractol.mlx_ptr, fractol.win_ptr, 1100, 660, 0xFF0000, "red"); // 287616
	// mlx_string_put(fractol.mlx_ptr, fractol.win_ptr, 1100, 670, 0x00FF00, "green"); // 15723752
	// mlx_string_put(fractol.mlx_ptr, fractol.win_ptr, 1100, 680, 0x0000FF, "turquoise"); // 215723752

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