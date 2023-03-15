/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:04:30 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/03/15 10:56:34 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

static unsigned int	select_from_palette(const int select)
{
	int	color[16];

	color[0] = 0x00235B;
	color[1] = 0xE21818;
	color[2] = 0xFFDD83;
	color[3] = 0x98DFD6;
	color[4] = 0x000764;
	color[5] = 0x539165;
	color[6] = 0x3F497F;
	color[7] = 0xF7C04A;
	color[8] = 0xF7C04A;
	color[9] = 0xF8F5E4;
	color[10] = 0xE9A178;
	color[11] = 0xA84448;
	color[12] = 0x7A3E65;
	color[13] = 0x2E4F4F;
	color[14] = 0x2C3333;
	color[15] = 0xCCD5AE;
	return (color[select]);
}

int	***convert_colors_to_rgb_arrays(void)
{
	int				***palette;
	int				i;
	int				j;
	unsigned int	color;

	j = 0;
	palette = (int ***)malloc(sizeof(int **) * 16);
	if (palette == NULL)
	{
		printf("malloc error1\n");
		exit (EXIT_FAILURE);
	}
	while (j < 16)
	{
		color = select_from_palette(j);
		palette[j] = (int **)malloc(sizeof(int *) * 3);
		if (palette[j] == NULL)
		{
			printf("malloc error2\n");
			exit (EXIT_FAILURE);
		}
		i = 0;
		while (i <= 3)
		{
			palette[j][i] = malloc(sizeof(int));
			if (palette[j][i] == NULL)
			{
				printf("malloc error3\n");
				exit (EXIT_FAILURE);
			}
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

t_palette	get_palette(t_fractol f, int iterations)
{
	int	range_end;
	int	select_first_color;
	int	select_second_color;

	f.palette.range_start = iterations - (iterations % f.palette.range);
	range_end = f.palette.range_start + f.palette.range;
	select_first_color = f.palette.range_start / f.palette.range % 16;
	select_second_color = range_end / f.palette.range % 16;
	f.palette.first = f.palette.converted[select_first_color];
	f.palette.second = f.palette.converted[select_second_color];
	return (f.palette);
}
