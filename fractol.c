/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoolhov <fkoolhov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 10:42:19 by felicia           #+#    #+#             */
/*   Updated: 2023/02/24 17:43:03 by fkoolhov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

static void	set_pixel_color(t_fractol *fractol, int x, int y, int color)
{
	int	first_byte;

	first_byte = x * 4 + y * fractol->image_width * 4;
	fractol->img_ptr->pixels[first_byte + 0] = color >> 24;
	fractol->img_ptr->pixels[first_byte + 1] = color >> 16;
	fractol->img_ptr->pixels[first_byte + 2] = color >> 8;
	fractol->img_ptr->pixels[first_byte + 3] = color;
}

double	normalize_iterations(t_fractol fractol, t_color c, int iterations, int x, int y)
{
	//int		division;
	double 	normalized;
    double 	log_zn = log(x * x + y * y) / 2;
	double 	nu = log(log_zn / log(2)) / log(2);

	fractol.change_color = 1;
    normalized = iterations + 1 - nu + 2;
	normalized = (normalized - c.range_start) / c.range;
	return (normalized);
}

int	interpolate_color(int first, int second, double amount)
{
	int	result;
	int	difference;

	difference = second - first;

	result = first + (difference * amount);
	return (result); 
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

	// color = 0;
	// *array[0] = (unsigned char)(sin(0.016 * normalized * 100 + 4) * 100 + color);
	// *array[1] = (unsigned char)(sin(0.013 * normalized * 100 + 2) * 100 + color);
	// *array[2] = (unsigned char)(sin(0.01 * normalized * 100 + 1) * 100 + color);

	// c.first = get_rgb(0xBFEFFF); // pastel blue
	// c.second = get_rgb(0xFCCA26); // orange
	return (array);
}

int	get_color(t_fractol fractol, t_color c, int iterations, int x, int y)
{
	unsigned int	color_as_int;
	double			normalized;

	if (iterations == fractol.max_iterations)
		return (255);
	normalized = normalize_iterations(fractol, c, iterations, x, y);

	// c.first = get_rgb(normalized, 10);
	// c.second = get_rgb(normalized, 300);
	unsigned int	channel_one = interpolate_color(*c.first[0], *c.second[0], normalized);
	unsigned int	channel_two = interpolate_color(*c.first[1], *c.second[1], normalized);
	unsigned int	channel_three = interpolate_color(*c.first[2], *c.second[2], normalized);
	unsigned int	channel_four = 0xFF;

	color_as_int = (channel_one << 24) + (channel_two << 16) + (channel_three << 8) + channel_four;
	//printf("color = %X\n", color_as_int);
	return (color_as_int);
}

int	mandelbrot(t_fractol fractol, int x, int y)
{
	double	real_a;
	double	imaginary_b;
	int		iterations;
	double	z_real;
	double	z_imaginary;
	double	tmp;

	real_a 		= fractol.move_horizontal + (x - fractol.image_width/fractol.complex_heigth)*fractol.complex_width/fractol.image_width;
	imaginary_b = fractol.move_vertical + (y - fractol.image_heigth/fractol.complex_heigth)*fractol.complex_width/fractol.image_width;
	z_real = 0;
	z_imaginary = 0;
	iterations = 0;
	fractol.threshold = 4;
	while (iterations < fractol.max_iterations)
	{
		fractol.z_n = z_real * z_real + z_imaginary * z_imaginary;
		if (fractol.z_n > fractol.threshold)
			return (iterations);
		tmp = 2 * z_real * z_imaginary + imaginary_b;
		z_real = z_real * z_real - z_imaginary * z_imaginary + real_a;
		z_imaginary = tmp;
		iterations++;
	}
	return (iterations);
}

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

void	render_image(t_fractol fractol)
{
	t_color	c;
	int		color;
	int		iterations = 0;
	int		x = 0;
	int		y = 0;

	if (fractol.img_ptr != NULL)
	 	mlx_delete_image(fractol.mlx_ptr, fractol.img_ptr); 
	fractol.img_ptr = mlx_new_image(fractol.mlx_ptr, fractol.image_width, fractol.image_heigth);
	while (y < fractol.image_heigth)
	{
		while (x < fractol.image_width)
		{
			if (fractol.mandelbrot == 1)
				iterations = mandelbrot(fractol, x, y);
			c = get_palette(c, iterations);
			color = get_color(fractol, c, iterations, x, y);
			set_pixel_color(&fractol, x, y, color);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_image_to_window(fractol.mlx_ptr, fractol.img_ptr, 0, 0);
}

void	scroll_hook(double xdelta, double ydelta, void *param)
{
	t_fractol	*fractol = param;
	double		temp_width = fractol->complex_width;
	double		temp_heigth = fractol->complex_heigth;

	xdelta++;
	if (ydelta > 0)
	{
		fractol->complex_width = fractol->complex_width * 0.95;
		fractol->move_horizontal = fractol->move_horizontal + ((temp_width - fractol->complex_width) / 2);
		fractol->complex_heigth = fractol->complex_heigth * 0.95;
		fractol->move_vertical = fractol->move_vertical + ((temp_heigth - fractol->complex_heigth) / 2);
		if (fractol->complex_width < fractol->image_width)
		fractol->max_iterations++;
	
	}
	else if (ydelta < 0)
	{
		fractol->complex_width = fractol->complex_width * 1.05;
		fractol->move_horizontal = fractol->move_horizontal - ((fractol->complex_width - temp_width) / 2);
		fractol->complex_heigth = fractol->complex_heigth * 1.05;
		fractol->move_vertical = fractol->move_vertical - ((fractol->complex_heigth - temp_heigth) / 2);
		if (fractol->max_iterations != 50)
			fractol->max_iterations--;
	}
	render_image(*fractol);
}

void	key_hook(mlx_key_data_t keydata, void *param)
{
	
	t_fractol	*fractol = param;

	if (keydata.key == MLX_KEY_DOWN) // down
		fractol->move_vertical = fractol->move_vertical + (fractol->complex_heigth / 50);
	else if (keydata.key == MLX_KEY_UP) // up
		fractol->move_vertical = fractol->move_vertical - (fractol->complex_heigth / 50);
	else if (keydata.key == MLX_KEY_RIGHT) // right
		fractol->move_horizontal = fractol->move_horizontal + (fractol->complex_width / 50);
	else if (keydata.key == MLX_KEY_LEFT) // left
		fractol->move_horizontal = fractol->move_horizontal - (fractol->complex_width / 50);
	else if (keydata.key == MLX_KEY_SPACE)
		fractol->change_color += 10;
	render_image(*fractol);
}

void resize_window(int32_t width, int32_t height, void* param)
{
	t_fractol	*fractol = param;

	fractol->image_width = width;
	fractol->image_heigth = height;
	render_image(*fractol);
}

int main(int argc, char **argv)
{
	t_fractol	fractol;

	if (argc > 2)
		fprintf(stderr, "too many args\n");
	if (argc < 1)
		fprintf(stderr, "too few args\n");
	if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
		fractol.mandelbrot = 1;
	// paramater setup, create function for?
	fractol.window_width = 400;
	fractol.window_heigth = 300;
	fractol.image_width = fractol.window_width;
	fractol.image_heigth = fractol.window_heigth;
	fractol.complex_width = 4.0;
	fractol.complex_heigth = 2.0;
	fractol.move_horizontal = 0.0;
	fractol.move_vertical = 0.0;
	fractol.img_ptr = NULL;
	fractol.zoom = 1;
	fractol.change_color = 1.0;
	fractol.max_iterations = 80;
	fractol.definition = 0;

	// basic mlx and window setup
	fractol.mlx_ptr = mlx_init(fractol.window_width, fractol.window_heigth, "fractol", true);
	if (fractol.mlx_ptr == NULL)
	    fprintf(stderr, "could not init\n");

	// basic graphic setup
	render_image(fractol);

	// event setup and handling
	mlx_resize_hook(fractol.mlx_ptr, &resize_window, &fractol);
	mlx_scroll_hook(fractol.mlx_ptr, &scroll_hook, &fractol);
	mlx_key_hook(fractol.mlx_ptr, &key_hook, &fractol);
	mlx_loop(fractol.mlx_ptr);

	return (0);
}