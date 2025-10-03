/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_output.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: GitHub Copilot                              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 00:00:00 by copilot           #+#    #+#             */
/*   Updated: 2025/10/03 00:00:00 by copilot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "rendering.h"
#include "math_inc.h"
#include <stdio.h>
#include <stdlib.h>

int	write_ppm_header(FILE *file, int width, int height)
{
	if (fprintf(file, "P3\n%d %d\n255\n", width, height) < 0)
		return (-1);
	return (0);
}

int	write_pixel_color(FILE *file, uint32_t color)
{
	int	r, g, b;
	
	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF; 
	b = (color >> 8) & 0xFF;
	
	if (fprintf(file, "%d %d %d ", r, g, b) < 0)
		return (-1);
	return (0);
}

uint32_t	get_pixel_color(int x, int y, t_scene *scene)
{
	t_ray	ray;
	
	ray = get_ray(x, y, scene->camera);
	loop_though_objects(&ray, scene->objects);
	
	if (ray.results.is_hit == 0)
		return (0x000000ff); // Black background
	else
		return (0xff00ffff); // Magenta for hit objects
}

int	render_to_ppm(t_scene *scene, const char *filename)
{
	FILE	*file;
	int		x, y;
	int		width, height;
	uint32_t	color;
	
	width = scene->camera->window_info.width;
	height = scene->camera->window_info.height;
	
	file = fopen(filename, "w");
	if (!file)
	{
		printf("Error: Cannot create file %s\n", filename);
		return (-1);
	}
	
	if (write_ppm_header(file, width, height) == -1)
	{
		fclose(file);
		return (-1);
	}
	
	printf("Rendering %dx%d image to %s...\n", width, height, filename);
	
	for (y = 0; y < height; y++)
	{
		for (x = 0; x < width; x++)
		{
			color = get_pixel_color(x, y, scene);
			if (write_pixel_color(file, color) == -1)
			{
				fclose(file);
				return (-1);
			}
		}
		fprintf(file, "\n");
		
		if (y % 50 == 0)
			printf("Progress: %d/%d lines\n", y, height);
	}
	
	fclose(file);
	printf("Image saved to %s\n", filename);
	return (0);
}
