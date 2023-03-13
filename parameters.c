/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:09:48 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/03/13 10:52:30 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

t_fractol	set_general_parameters(t_fractol fractol)
{
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

t_fractol	set_parameters_julia(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc != 4)
	{
		ft_putendl_fd("Error: Incorrect number of arguments.\n"
			"Input should be: [./fractol] [julia]"
			"[real component of c] [imaginary component of c]\n"
			"For example: ./fractol julia 0.4 0.2", 2);
		exit (EXIT_FAILURE);
	}
	fractol.c_real = ft_atof(argv[2]);
	fractol.c_imaginary = ft_atof(argv[3]);
	if (fractol.c_real == -42 || fractol.c_imaginary == -42
		|| fractol.c_real < -2.0 || fractol.c_real > 2.0
		|| fractol.c_imaginary < -2.0 || fractol.c_imaginary > 2.0)
	{
		ft_putendl_fd("Error: Julia parameters must be fractional numbers "
			"between -2.0 and 2.0. No spaces allowed.\n"
			"For example: ./fractol julia 0.4 0.2", 2);
		exit (EXIT_FAILURE);
	}
	fractol.palette.range = 20;
	fractol.julia = 1;
	fractol = set_general_parameters(fractol);
	return (fractol);
}

t_fractol	set_parameters_mandelbrot(int argc)
{
	t_fractol	fractol;

	if (argc > 2)
	{
		ft_putendl_fd("Error: Too many arguments.\n"
			"Input should be: [./fractol] [mandelbrot]", 2);
		exit (EXIT_FAILURE);
	}
	fractol.palette.range = 50;
	fractol.mandelbrot = 1;
	fractol = set_general_parameters(fractol);
	return (fractol);
}
