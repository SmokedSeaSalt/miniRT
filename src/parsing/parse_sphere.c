/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:59:33 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/25 12:18:36 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>		//to use free
#include <stdio.h>		//to use printf
#include "parsing.h"
#include "helpers.h"
#include "libft.h"
#include "structs.h"

static int	fill_sphere_struct(t_sphere *sphere, char **line)
{
	if (count_arguments(line) != 8)
		return (printf("Sphere: Incorrect amount of arguments\n"), 1);
	sphere->coords = fill_vec3(line[1], line[2], line[3]);
	sphere->diameter = ft_atof(line[4]);
	sphere->color = fill_color(line[5], line[6], line[7]);
	if (color_out_of_range(sphere->color))
		return (printf("Sphere: Color out of range\n"), 1);
	return (0);
}

int	new_sphere_struct(t_scene *scene, char **line)
{
	t_sphere	*sphere;
	t_object	*object;

	sphere = ft_calloc(1, sizeof(t_sphere));
	if (sphere == NULL)
		return (printf("Malloc fail\n"), 2);
	if (fill_sphere_struct(sphere, line) != 0)
		return (free(sphere), 1);
	object = ft_calloc(1, sizeof(t_object));
	if (object == NULL)
		return (free (sphere), printf("Malloc fail\n"), 2);
	object->type = SPHERE;
	object->data = sphere;
	add_object_to_back(&(scene->objects), object);
	return (0);
}
