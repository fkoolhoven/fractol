/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:42:19 by felicia           #+#    #+#             */
/*   Updated: 2023/03/15 15:30:09 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static void	check_for_setup_errors(t_fractol fractol)
{
	if (fractol.mlx_ptr == NULL)
	{
		ft_putendl_fd("Error: Could not "
			"initialize a new MLX instance", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	if (fractol.img_ptr == NULL)
	{
		ft_putendl_fd("Error: Could not "
			"allocate new image buffer", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	if (fractol.palette.converted == NULL)
	{
		ft_putstr_fd("Error: Could not "
			"malloc palette", STDERR_FILENO);
		free_palette(fractol.palette.converted);
		exit (EXIT_FAILURE);
	}
}

static t_fractol	initial_setup(t_fractol fractol)
{
	fractol.mlx_ptr = mlx_init(fractol.window_width, fractol.window_height,
			"fractol", true);
	if (fractol.mlx_ptr == NULL)
		return (fractol);
	fractol.img_ptr = mlx_new_image(fractol.mlx_ptr, fractol.image_width,
			fractol.image_height);
	if (fractol.img_ptr == NULL)
		return (fractol);
	fractol.palette.converted = convert_colors_to_rgb_arrays();
	if (fractol.palette.converted == NULL)
		return (fractol);
	mlx_image_to_window(fractol.mlx_ptr, fractol.img_ptr, 0, 0);
	render_image(fractol);
	mlx_scroll_hook(fractol.mlx_ptr, &mouse_scroll, &fractol);
	mlx_key_hook(fractol.mlx_ptr, &key_press, &fractol);
	mlx_resize_hook(fractol.mlx_ptr, &resize_window, &fractol);
	return (fractol);
}

static t_fractol	validate_input(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc < 2)
	{
		ft_putendl_fd("Error: Too few arguments\n"
			"Input should be: ./fractol [fractaltype]\n"
			"Fractaltype options are: \"mandelbrot\" and \"julia\"", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
		fractol = set_parameters_mandelbrot(argc);
	else if (ft_strncmp(argv[1], "julia", 6) == 0)
		fractol = set_parameters_julia(argc, argv);
	else
	{
		ft_putendl_fd("Error: Incorrect fractaltype\n"
			"Input should be: ./fractol [fractaltype]\n"
			"Fractaltype options are: \"mandelbrot\" and \"julia\"", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	return (fractol);
}

int	main(int argc, char **argv)
{
	t_fractol	fractol;

	fractol = validate_input(argc, argv);
	fractol = initial_setup(fractol);
	check_for_setup_errors(fractol);
	mlx_loop(fractol.mlx_ptr);
	free_palette(fractol.palette.converted);
	mlx_delete_image(fractol.mlx_ptr, fractol.img_ptr);
	return (EXIT_SUCCESS);
}
