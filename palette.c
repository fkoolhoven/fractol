/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:04:30 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/03/07 11:49:07 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

static int	select_from_palette(const int range)
{
	int	colors[7];

	colors[0] = 0x8CB5B5;
	colors[1] = 0xEC410B;
	colors[2] = 0x506432;
	colors[3] = 0xFFA400;
	colors[4] = 0xC0413B;
	colors[5] = 0xB30019;
	colors[6] = 0x80003A;
	return (colors[range % 7]);
}

int	**get_rgb(unsigned int color)
{
	int	**array;
	int	i;

	array = (int **)malloc(sizeof(int *) * 3);
	i = 0;
	while (i <= 3)
	{
		array[i] = malloc(sizeof(int));
		i++;
	}
	*array[2] = color % 256;
	*array[1] = ((color - *array[2]) / 256) % 256;
	*array[0] = ((color - *array[1]) / 256 / 256) - *array[2] / 256;
	return (array);
}

t_color	get_palette(int iterations)
{
	t_color	palette;
	int		range_end;

	palette.range = 50;
	palette.range_start = iterations - (iterations % 50);
	range_end = palette.range_start + 50;
	palette.first = get_rgb(select_from_palette(palette.range_start));
	palette.second = get_rgb(select_from_palette(range_end));
	return (palette);
}
