/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:42:19 by felicia           #+#    #+#             */
/*   Updated: 2023/03/08 16:20:28 by fkoolhov         ###   ########.fr       */
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
			//printf("iterations = %i\nmax = %i\n", iterations, fractol.max_iterations);
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

t_fractol	set_parameters(char **argv)
{
	t_fractol	fractol;

	if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
		fractol.mandelbrot = 1;
	else if (ft_strncmp(argv[1], "julia", 6) == 0)
	{
		fractol.julia = 1;
		fractol.c = ft_atoi(argv[2]);
	}
		
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
	fractol.max_iterations = 100;
	fractol.mlx_ptr = mlx_init(fractol.window_width, fractol.window_heigth,
			"fractol", true);
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

	// if (argc > 2)
	// {
	// 	ft_putendl_fd("Error: Too many arguments\n[./fractol] [fractaltype]", 2);
	// 	exit (EXIT_FAILURE);
	// }
	if (argc < 2)
	{
		ft_putendl_fd("Error: Too few arguments\n[./fractol] [fractaltype]", 2);
		exit (EXIT_FAILURE);
	}
	fractol = set_parameters(argv);
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
	return (EXIT_SUCCESS);
}
