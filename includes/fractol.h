/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:12:08 by felicia           #+#    #+#             */
/*   Updated: 2023/02/24 17:43:00 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "libft/libft.h"
#include "MLX42.h"
#include <stdio.h>
#include <math.h>

// =====STRUCTS=================================================================

typedef struct s_fractol
{
	int			mandelbrot;
	mlx_t		*mlx_ptr;
	mlx_image_t	*img_ptr;
	int     	window_width;
	int     	window_heigth;
	int  		image_width;
	int  		image_heigth;
	double		complex_width;
	double		complex_heigth;
	double		move_vertical;
	double		move_horizontal;
	int			max_iterations;
	int			threshold;
	int			z_n;
	double		zoom;
	double		change_color;
	int			definition;
	int			range;
	int			division;
}	t_fractol;

typedef struct s_color
{
	int			**second;
	int			**first;
	int			range;
	int			range_start;
	int			division;
}	t_color;

// =====FUNCTIONS===============================================================

#endif