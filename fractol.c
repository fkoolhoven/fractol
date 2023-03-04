/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:42:19 by felicia           #+#    #+#             */
/*   Updated: 2023/03/04 16:51:36 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int	mandelbrot(t_fractol fractol, int x, int y)
{
	double	real_a;
	double	imaginary_b;
	double	z_real;
	double	z_imaginary;
	double	tmp;

	real_a 		= fractol.move_horizontal + (x - fractol.image_width / fractol.complex_heigth) * fractol.complex_width / fractol.image_width;
	imaginary_b = fractol.move_vertical + (y - fractol.image_heigth / fractol.complex_heigth) * fractol.complex_width / fractol.image_width;
	z_real = 0.0;
	z_imaginary = 0.0;
	fractol.iterations = 0;
	fractol.threshold = 4;
	while (fractol.iterations < fractol.max_iterations)
	{
		fractol.z_n = z_real * z_real + z_imaginary * z_imaginary;
		if (fractol.z_n > fractol.threshold)
			return (fractol.iterations);
		tmp = 2 * z_real * z_imaginary + imaginary_b;
		z_real = z_real * z_real - z_imaginary * z_imaginary + real_a;
		z_imaginary = tmp;
		fractol.iterations++;
	}
	return (fractol.iterations);
}

void	render_image(t_fractol fractol)
{
	t_color	palette;
	int		color;
	int		iterations;
	int		x;
	int		y;

	iterations = 0;
	x = 0;
	y = 0;
	while (y < fractol.image_heigth)
	{
		while (x < fractol.image_width)
		{
			if (fractol.mandelbrot == 1)
				iterations = mandelbrot(fractol, x, y);
			if (iterations == fractol.max_iterations)
				color = 0x000000FF;
			else
			{
				palette = get_palette(iterations);
				color = get_color(palette, iterations, x, y);
			}
			set_pixel_color(&fractol, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_image_to_window(fractol.mlx_ptr, fractol.img_ptr, 0, 0);
}

t_fractol	set_parameters(char **argv)
{
	t_fractol	fractol;

	if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
		fractol.mandelbrot = 1;
	fractol.window_width = 400;
	fractol.window_heigth = 300;
	fractol.image_width = fractol.window_width;
	fractol.image_heigth = fractol.window_heigth;
	fractol.complex_width = 4.0;
	fractol.complex_heigth = 2.0;
	fractol.move_horizontal = 0.0;
	fractol.move_vertical = 0.0;
	fractol.zoom = 1;
	fractol.img_ptr = NULL;
	fractol.max_iterations = 80;
	fractol.mlx_ptr = mlx_init(fractol.window_width, fractol.window_heigth, "fractol", true);
	if (fractol.mlx_ptr == NULL)
	{
		ft_putendl_fd("Could not initialize a new MLX instance", 2);
		exit (EXIT_FAILURE);
	}
	return (fractol);
}

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc > 2)
	{
		ft_putendl_fd("Error: Too many arguments\n[./fractol] [fractaltype]", 2);
		exit (EXIT_FAILURE);
	}
	if (argc < 2)
	{
		ft_putendl_fd("Error: Too few arguments\n[./fractol] [fractaltype]", 2);
		exit (EXIT_FAILURE);
	}
	fractol = set_parameters(argv);
	fractol.img_ptr = mlx_new_image(fractol.mlx_ptr, fractol.image_width, fractol.image_heigth);
	mlx_image_to_window(fractol.mlx_ptr, fractol.img_ptr, 0, 0);
	render_image(fractol);
	mlx_resize_hook(fractol.mlx_ptr, &resize_window, &fractol);
	mlx_scroll_hook(fractol.mlx_ptr, &scroll_hook, &fractol);
	mlx_key_hook(fractol.mlx_ptr, &key_hook, &fractol);
	mlx_loop(fractol.mlx_ptr);
	mlx_delete_image(fractol.mlx_ptr, fractol.img_ptr);
	return (EXIT_SUCCESS);
}