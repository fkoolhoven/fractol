/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:42:19 by felicia           #+#    #+#             */
/*   Updated: 2023/02/16 17:16:46 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

static void	set_pixel_color(t_fractol *fractol, int x, int y, int color)
{
	int	first_byte;

	first_byte = x * 4 + y * fractol->image_width * 4;
	fractol->img_ptr->pixels[first_byte + 0] = color >> 24;
	//printf("first %i\n", fractol->img_ptr->pixels[first_byte + 0]);
	fractol->img_ptr->pixels[first_byte + 1] = color >> 16;
	//printf("second %i\n", fractol->img_ptr->pixels[first_byte + 1]);
	fractol->img_ptr->pixels[first_byte + 2] = color >> 8;
	//printf("third %i\n", fractol->img_ptr->pixels[first_byte + 2]);
	fractol->img_ptr->pixels[first_byte + 3] = color;
	//printf("fourth %i\n", fractol->img_ptr->pixels[first_byte + 3]);
}

int	get_color(int iterations)
{
	if (iterations >= 0 && iterations <= 10)
		return (0xFF0000FF); // red
	else if (iterations >= 11 && iterations <= 20)
		return (0xE2147BFF); // dark pink
	else if (iterations >= 21 && iterations <= 39)
		return (0xCCFFCCFF); // pastel green
	else if (iterations >= 40 && iterations <= 48)
		return (0x1D1DA1FF); // dark blue
	else if (iterations >= 49 && iterations <= 46)
		return (0xF90F7CFF); // bright pink
	else if (iterations >= 47 && iterations <= 53)
		return (0xFF9E0AFF); // peachy orange
	else if (iterations >= 54 && iterations <= 60)
		return (0x26B6F3FF); // blue
	else if (iterations >= 61 && iterations <= 66)
		return (0xB2FCF9FF); // pastel blue
	else if (iterations >= 67 && iterations <= 71)
		return (0xFFFFCCFF); // pastel pink
	else if (iterations >= 72 && iterations <= 75)
		return (0x146B14FF); // dark green
	else if (iterations >= 76 && iterations <= 77)
		return (0x990000FF); // dark red
	else if (iterations >= 78 && iterations <= 79)
		return (0xF7FF00FF); // bright yellow
	else if (iterations >= 80 && iterations <= 81)
		return (0x4E48F6FF); // semi dark blue
	else if (iterations == 82)
		return (0x000000FF); // black
	return (0xFFFFFFFF); // white
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
	fractol.max_iterations = 82;
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
	 	mlx_delete_image(fractol.mlx_ptr, fractol.img_ptr); 
	fractol.img_ptr = mlx_new_image(fractol.mlx_ptr, fractol.image_width, fractol.image_heigth);
	
	while (y < fractol.image_heigth)
	{
		while (x < fractol.image_width)
		{
			if (fractol.mandelbrot == 1)
				iterations = mandelbrot(fractol, x, y);
			color = get_color(iterations);
			set_pixel_color(&fractol, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_image_to_window(fractol.mlx_ptr, fractol.img_ptr, 0, 0);
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fractol	*fractol = param;

	xdelta++;
	if (ydelta > 0)
	{
		fractol->complex_width = fractol->complex_width * 0.95;
		//fractol->move_horizontal = fractol->move_horizontal * 1.1;
		fractol->complex_heigth = fractol->complex_heigth * 0.95;
		//fractol->move_vertical = fractol->move_vertical * 1.1;
	
	}
	else if (ydelta < 0)
	{
		fractol->complex_width = fractol->complex_width * 1.05;
		fractol->move_horizontal = fractol->move_horizontal - 0.1;
		fractol->complex_heigth = fractol->complex_heigth * 1.05;
		fractol->move_vertical = fractol->move_vertical - 0.1;
	}
	render_image(*fractol);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	
	t_fractol	*fractol = param;

	if (keydata.key == MLX_KEY_DOWN) // down
		fractol->move_vertical = fractol->move_vertical + (fractol->complex_heigth / 50);
	else if (keydata.key == MLX_KEY_UP) // up
		fractol->move_vertical = fractol->move_vertical - (fractol->complex_heigth / 50);
	else if (keydata.key == MLX_KEY_RIGHT) // right
		fractol->move_horizontal = fractol->move_horizontal + (fractol->complex_width / 50);
	else if (keydata.key == MLX_KEY_LEFT) // left
		fractol->move_horizontal = fractol->move_horizontal - (fractol->complex_width / 50);
	render_image(*fractol);
}

int main(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc > 2)
		fprintf(stderr, "too many args\n");
	if (argc < 1)
		fprintf(stderr, "too few args\n");
	if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
		fractol.mandelbrot = 1;
	// paramater setup, create function for?
	fractol.window_width = 600;
	fractol.window_heigth = 400;
	fractol.image_width = fractol.window_width;
	fractol.image_heigth = fractol.window_heigth;
	fractol.complex_width = 4.0;
	fractol.complex_heigth = 2.0;
	fractol.move_horizontal = 0.0;
	fractol.move_vertical = 0.0;
	fractol.img_ptr = NULL;
	fractol.zoom = 1;

	// basic mlx and window setup
	fractol.mlx_ptr = mlx_init(fractol.window_width, fractol.window_heigth, "fractol", true);
	if (fractol.mlx_ptr == NULL)
	    fprintf(stderr, "could not init\n");

	// basic graphic setup
	render_image(fractol);

	// event setup and handling
	mlx_scroll_hook(fractol.mlx_ptr, &scroll_hook, &fractol);
	mlx_key_hook(fractol.mlx_ptr, &key_hook, &fractol);
	mlx_loop(fractol.mlx_ptr);

	return (0);
}