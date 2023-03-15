/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 10:37:46 by fkoolhov          #+#    #+#             */
/*   Updated: 2023/03/15 15:26:14 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static double	convert_to_double(char *str, int i)
{
	double	number;
	double	div;

	number = 0;
	div = 0.1;
	while (str[i] && ft_isdigit(str[i]) && str[i] != '.')
	{
		number = (number * 10.0) + (str[i] - '0');
		i++;
	}
	if (str[i] == '.')
		i++;
	while (str[i] && ft_isdigit(str[i]))
	{
		number = number + ((str[i] - '0') * div);
		div *= 0.1;
		i++;
	}
	if (str[i] && !ft_isdigit(str[i]))
		return (-42);
	return (number);
}

double	ft_atod(char *str)
{
	double	number;
	int		negative;
	int		i;

	negative = 1;
	i = 0;
	if (str[i] == '-')
	{
		negative = -1;
		i++;
	}
	number = convert_to_double(str, i);
	if (number == -42)
		return (number);
	return (number * negative);
}
