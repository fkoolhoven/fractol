/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parameters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/12 18:09:48 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/03/03 23:04:47 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void set_general_parameters(t_fractol *fractol)
{
	fractol->window_width = WINDOW_WIDTH;
	fractol->window_height = WINDOW_HEIGHT;
	fractol->image_width = fractol->window_width;
	fractol->image_height = fractol->window_height;
	fractol->complex_width = 4.0;
	fractol->complex_height = 2.0;
	fractol->move_horizontal = 0.0;
	fractol->move_vertical = 0.0;
	fractol->threshold = 4;
	fractol->max_iterations = 100;
}

t_fractol	*set_parameters_julia(int argc, char **argv)
{
	t_fractol	*fractol;

	if (argc != 4)
	{
		ft_putendl_fd("Error: Incorrect number of arguments.\n"
			"Input should be: ./fractol julia "
			"[real component of c] [imaginary component of c]\n"
			"For example: ./fractol julia -0.538 0.50695", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	fractol = malloc(sizeof(t_fractol));
	if (fractol == NULL)
	{
		ft_putendl_fd("Error: Could not "
			"allocate fractol struct", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	fractol->c_real = ft_atod(argv[2]);
	fractol->c_imaginary = ft_atod(argv[3]);
	if (fractol->c_real < -2.0 || fractol->c_real > 2.0
		|| fractol->c_imaginary < -2.0 || fractol->c_imaginary > 2.0)
	{
		ft_putendl_fd("Error: Julia parameters must be fractional numbers "
			"between -2.0 and 2.0. No spaces allowed.\n"
			"For example: ./fractol julia -0.538 0.50695", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	fractol->palette.range = 20;
	fractol->julia = 1;
	set_general_parameters(fractol);
	return (fractol);
}

t_fractol	*set_parameters_mandelbrot(int argc)
{
	t_fractol	*fractol;

	if (argc > 2)
	{
		ft_putendl_fd("Error: Too many arguments.\n"
			"Input should be: ./fractol mandelbrot", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	fractol = malloc(sizeof(t_fractol));
	if (fractol == NULL)
	{
		ft_putendl_fd("Error: Could not "
			"allocate fractol struct", STDERR_FILENO);
		exit (EXIT_FAILURE);
	}
	fractol->palette.range = 45;
	fractol->mandelbrot = 1;
	set_general_parameters(fractol);
	return (fractol);
}
