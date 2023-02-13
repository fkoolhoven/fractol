/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 17:12:08 by felicia           #+#    #+#             */
/*   Updated: 2023/02/10 19:58:15 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

//# include "libft/libft.h"
#include "mlx.h"
#include <stdio.h>
#include <math.h>

// =====STRUCTS=================================================================

typedef struct s_fractol
{
	void    *mlx_ptr;
	void    *win_ptr;
	void	*img_ptr;
	int		bits_per_pixel;
	int		size_len;
	int		endian;
	char	*buf;
	int     window_width;
	int     window_heigth;
	int  	image_width;
	int  	image_heigth;
	double	complex_width;
	double	complex_heigth;
	double	move_vertical;
	double	move_horizontal;
	int		max_iterations;
}	t_fractol;

// =====FUNCTIONS===============================================================

#endif