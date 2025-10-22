/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:59:15 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/22 15:05:36 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>		//to use printf
#include <stdlib.h>		//to use free
#include "parsing.h"
#include "helpers.h"
#include "libft.h"
#include "structs.h"
#include "math_inc.h"

static int	fill_light_struct(t_lights *light, char **line)
{
	if (count_arguments(line) != 8)
		return (printf("Error\nLight: Incorrect amount of arguments\n"), 1);
	light->coords = fill_vec3(line[1], line[2], line[3]);
	light->brightness = ft_atof(line[4]);
	if (light->brightness < 0.0 || light->brightness > 1.0)
		return (printf("Error\nLight: Brightness out of range\n"), 1);
	light->color = fill_color(line[5], line[6], line[7]);
	if (color_out_of_range(light->color))
		return (printf("Error\nLight: Color out of range\n"), 1);
	light->color_brightness = vec3_new( \
light->brightness * ((float)light->color.r / 255.0f), \
light->brightness * ((float)light->color.g / 255.0f), \
light->brightness * ((float)light->color.b / 255.0f));
	return (0);
}

int	new_light_struct(t_scene *scene, char **line)
{
	t_lights	*light;

	light = ft_calloc(1, sizeof(t_lights));
	if (light == NULL)
		return (printf("Error\nMalloc fail\n"), 2);
	if (fill_light_struct(light, line) != 0)
		return (free(light), 1);
	light->next = scene->lights;
	scene->lights = light;
	return (0);
}
