/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:04:30 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/03/01 12:08:53 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

static int	palette(const int range)
{
	const int	colors[7] = {
		0x830713, // dark red
		0xC4F7FA, // light blue
		0x55149F, // dark purple
		0xFFCD03, // orange
		0xF30BEB, // pink
		0xC2FCC0, // pastel green
		0x176414, // dark green
	};

	return (colors[range % 7]);
}

int	**get_rgb(unsigned int color)
{
    int **array;
    int i;

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

t_color	get_palette(t_color c, int iterations)
{
	int	range_end;

	c.range = 50;
	c.range_start = iterations - (iterations % 50);
	range_end = c.range_start + 50;
	c.first = get_rgb(palette(c.range_start));
	c.second  = get_rgb(palette(range_end));
	return (c);
}