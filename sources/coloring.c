/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coloring.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 11:58:24 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/03/15 11:24:57 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static int	interpolate_color(int first_color, int second_color, float amount)
{
	int	result;

	result = first_color + (second_color - first_color) * amount;
	return (result);
}

static float	normalize_iterations(t_palette c, int iterations, int x, int y)
{
	float	amount;
	float	current_log;

	current_log = log(x * x + y * y) / 2;
	amount = iterations - (log((current_log) / log(2)) / log(2)) + 3;
	amount = (amount - c.range_start) / c.range;
	if (amount > 1)
		amount = 1;
	else if (amount < 0)
		amount = 0;
	return (amount);
}

int	get_color(t_palette c, int iterations, int x, int y)
{
	unsigned int	color;
	float			amount;

	amount = normalize_iterations(c, iterations, x, y);
	color = interpolate_color(*c.first[0], *c.second[0], amount) << 24;
	color += interpolate_color(*c.first[1], *c.second[1], amount) << 16;
	color += interpolate_color(*c.first[2], *c.second[2], amount) << 8;
	color += 0xFF;
	return (color);
}
