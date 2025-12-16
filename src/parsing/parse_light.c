/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:59:15 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/16 14:09:42 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>		//to use printf
#include <stdlib.h>		//to use free
#include "parsing.h"
#include "helpers.h"
#include "libft.h"
#include "structs.h"
#include "math_inc.h"
#include "consts.h"

static int	fill_light_struct(t_lights *light, char **line)
{
	if (count_arguments(line) != 4)
		return (printf("Error\nLight: "N_ARGS_ERR"\n"), 1);
	if (parse_orig(&(light->coords), line[1]) != 0)
		return (printf("Light: Origin parsing error\n"), 1);
	if (parse_ratio(&(light->brightness), line[2]) != 0)
		return (printf("Light: Ratio parsing error\n"), 1);
	if (parse_color(&(light->color), line[3]) != 0)
		return (printf("Light: Color parsing error\n"), 1);
	light->color_brightness = vec3_new(\
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
