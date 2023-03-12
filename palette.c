/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:04:30 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/03/12 18:32:11 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

unsigned int	select_from_palette(const int select)
{
	int	colors[7];

	colors[0] = 0x8CB5B5;
	colors[1] = 0xEC410B;
	colors[2] = 0x506432;
	colors[3] = 0xFFA400;
	colors[4] = 0xC0413B;
	colors[5] = 0xB30019;
	colors[6] = 0x80003A;
	return (colors[select]);
}

int	***convert_colors_to_rgb_arrays(void)
{
	int				***palette;
	int				i;
	int				j;
	unsigned int	color;

	j = 0;
	palette = (int ***)malloc(sizeof(int **) * 7);
	while (j < 7)
	{
		color = select_from_palette(j);
		palette[j] = (int **)malloc(sizeof(int *) * 3);
		i = 0;
		while (i <= 3)
		{
			palette[j][i] = malloc(sizeof(int));
			i++;
		}
		*palette[j][2] = color % 256;
		*palette[j][1] = ((color - *palette[j][2]) / 256) % 256;
		*palette[j][0] = ((color - *palette[j][1]) / 256 / 256)
			- *palette[j][2] / 256;
		j++;
	}
	return (palette);
}

t_color	get_palette(t_fractol f, int iterations)
{
	int		range_end;

	f.palette.range_start = iterations - (iterations % f.palette.range);
	range_end = f.palette.range_start + f.palette.range;
	f.palette.first = f.palette.converted_palette[f.palette.range_start % 7];
	f.palette.second = f.palette.converted_palette[range_end % 7];
	return (f.palette);
}
