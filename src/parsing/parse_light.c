/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:59:15 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/25 12:18:12 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>		//to use printf
#include <stdlib.h>		//to use free
#include "parsing.h"
#include "helpers.h"
#include "libft.h"
#include "structs.h"

static int	fill_light_struct(t_light *light, char **line)
{
	if (count_arguments(line) != 8)
		return (printf("Light: Incorrect amount of arguments\n"), 1);
	light->coords = fill_vec3(line[1], line[2], line[3]);
	light->brightness = ft_atof(line[4]);
	if (light->brightness < 0.0 || light->brightness > 1.0)
		return (printf("Light: Brightness out of range\n"), 1);
	light->color = fill_color(line[5], line[6], line[7]);
	if (color_out_of_range(light->color))
		return (printf("Light: Color out of range\n"), 1);
	return (0);
}

int	new_light_struct(t_scene *scene, char **line)
{
	t_light	*light;

	if (scene->light != NULL)
		return (printf("Light: Does not support multiple elements\n"), 1);
	light = ft_calloc(1, sizeof(t_light));
	if (light == NULL)
		return (printf("Malloc fail\n"), 2);
	if (fill_light_struct(light, line) != 0)
		return (free(light), 1);
	scene->light = light;
	return (0);
}
