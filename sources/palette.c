/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   palette.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: felicia <felicia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:04:30 by fkoolhov          #+#    #+#             */
/*   Updated: 2024/03/03 23:04:44 by felicia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

void	free_palette(int ***palette)
{
	int	j;

	j = 0;
	while (palette && palette[j] && j < 16)
	{
		if (palette[j][0])
			free(palette[j][0]);
		if (palette[j][1])
			free(palette[j][1]);
		if (palette[j][2])
			free(palette[j][2]);
		if (palette[j])
			free(palette[j]);
		j++;
	}
	if (palette)
		free(palette);
}

static int	***fill_palette(int ***palette, int j, unsigned int color)
{
	*palette[j][2] = color % 256;
	*palette[j][1] = ((color - *palette[j][2]) / 256) % 256;
	*palette[j][0] = ((color - *palette[j][1]) / 256 / 256)
		- *palette[j][2] / 256;
	return (palette);
}

static int	***malloc_color_array(int ***palette, int j)
{
	int	i;

	palette[j] = (int **)ft_calloc(3, sizeof(int *));
	if (palette[j] == NULL)
	{
		free_palette(palette);
		return (NULL);
	}
	i = 0;
	while (i < 3)
	{
		palette[j][i] = ft_calloc(1, sizeof(int));
		if (palette[j][i] == NULL)
		{
			free_palette(palette);
			return (NULL);
		}
		i++;
	}
	return (palette);
}

int	***convert_colors_to_rgb_arrays(void)
{
	int				***palette;
	int				j;
	unsigned int	color;

	j = 0;
	palette = (int ***)ft_calloc(16, sizeof(int **));
	if (palette == NULL)
		return (NULL);
	while (j < 16)
	{
		palette = malloc_color_array(palette, j);
		if (palette == NULL)
			return (NULL);
		color = select_from_palette(j);
		palette = fill_palette(palette, j, color);
		j++;
	}
	return (palette);
}
