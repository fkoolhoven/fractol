/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:58:24 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/03/03 23:04:29 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	interpolate_color(int first_color, int second_color, float amount)
{
	int	result;

	result = first_color + (second_color - first_color) * amount;
	return (result);
}

static float	normalize_iterations(t_palette *c, int iterations, int x, int y)
{
	float	amount;
	float	current_log;

	current_log = log(x * x + y * y) / 2;
	amount = iterations - (log((current_log) / log(2)) / log(2)) + 3;
	amount = (amount - c->range_start) / c->range;
	if (amount > 1)
		amount = 1;
	else if (amount < 0)
		amount = 0;
	return (amount);
}

static unsigned int	get_depth_shade(t_palette *c, int iterations, int x, int y)
{
	unsigned int	color;
	float			amount;

	amount = normalize_iterations(c, iterations, x, y);
	color = interpolate_color(*c->first[0], *c->second[0], amount) << 24;
	color += interpolate_color(*c->first[1], *c->second[1], amount) << 16;
	color += interpolate_color(*c->first[2], *c->second[2], amount) << 8;
	color += 0xFF;
	return (color);
}

unsigned int	get_color(t_fractol *f, int iterations, int x, int y)
{
	unsigned int	color;
	int				range_end;
	int				select_first_color;
	int				select_second_color;

	if (iterations == f->max_iterations)
		return (0x000000FF);
	f->palette.range_start = iterations - (iterations % f->palette.range);
	range_end = f->palette.range_start + f->palette.range;
	select_first_color = f->palette.range_start / f->palette.range % 16;
	select_second_color = range_end / f->palette.range % 16;
	f->palette.first = f->palette.converted[select_first_color];
	f->palette.second = f->palette.converted[select_second_color];
	color = get_depth_shade(&f->palette, iterations, x, y);
	return (color);
}
