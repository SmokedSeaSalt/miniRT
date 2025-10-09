/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:59:33 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/09 10:24:24 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>		//to use free
#include <stdio.h>		//to use printf
#include "parsing.h"
#include "helpers.h"
#include "libft.h"
#include "structs.h"
#include "math_inc.h"
#include "rendering.h"

static int	fill_sphere_struct(t_sphere *sphere, char **line)
{
	if (count_arguments(line) != 8)
		return (printf("Sphere: Incorrect amount of arguments\n"), 1);
	sphere->coords = fill_vec3(line[1], line[2], line[3]);
	sphere->diameter = ft_atof(line[4]);
	if (sphere->diameter < 0.0f)
		return (printf("Sphere: Negative diameter not allowed"));
	sphere->radius = sphere->diameter * 0.5f;
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
	object->is_hit = (int (*)(t_ray *, void *))is_hit_sphere;
	object->get_hit_dist = (float (*)(t_ray *, void *))get_hit_dist_sphere;
	object->get_hit_data = (void (*)(t_ray *, void *, t_scene *))get_hit_data_sphere;
	add_object_to_back(&(scene->objects), object);
	return (0);
}
