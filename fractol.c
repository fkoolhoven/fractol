/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:42:19 by felicia           #+#    #+#             */
/*   Updated: 2023/03/13 10:52:52 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	render_image(t_fractol fractol)
{
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

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc < 2)
	{
		ft_putendl_fd("Error: Too few arguments\n"
			"Input should be: [./fractol] [fractaltype]", 2);
		exit (EXIT_FAILURE);
	}
	if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
		fractol = set_parameters_mandelbrot(argc);
	else if (ft_strncmp(argv[1], "julia", 6) == 0)
		fractol = set_parameters_julia(argc, argv);
	else
	{
		ft_putendl_fd("Error: Incorrect fractaltype\n"
			"Input should be: [./fractol] [fractaltype]\n"
			"Fractaltype options are: [mandelbrot] or [julia]", 2);
		exit (EXIT_FAILURE);
	}
	fractol.img_ptr = mlx_new_image(fractol.mlx_ptr, fractol.image_width,
			fractol.image_heigth);
	mlx_image_to_window(fractol.mlx_ptr, fractol.img_ptr, 0, 0);
	fractol.palette.converted_palette = convert_colors_to_rgb_arrays();
	render_image(fractol);
	mlx_resize_hook(fractol.mlx_ptr, &resize_window, &fractol);
	mlx_scroll_hook(fractol.mlx_ptr, &scroll_hook, &fractol);
	mlx_key_hook(fractol.mlx_ptr, &key_hook, &fractol);
	mlx_loop(fractol.mlx_ptr);
	mlx_delete_image(fractol.mlx_ptr, fractol.img_ptr);
	// free palette
	return (EXIT_SUCCESS);
}
