/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:59:33 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/23 16:22:18 by mvan-rij         ###   ########.fr       */
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
#include "consts.h"
#include <math.h>

static int	fill_sphere_struct(t_sphere *sphere, char **line,
		t_texture_list *list)
{
	if (count_arguments(line) < 4 || count_arguments(line) > 6)
		return (printf("Error\nSphere: Incorrect amount of arguments\n"), 1);
	if (parse_orig(&(sphere->coords), line[1]) != 0)
		return (printf("Sphere: Origin parsing error\n"), 1);
	sphere->diameter = fabs(ft_atof(line[2]));
	sphere->radius = sphere->diameter * 0.5f;
	if (parse_color(&(sphere->color), line[3]) != 0)
		return (printf("Sphere: Color parsing error\n"), 1);
	if (count_arguments(line) >= 5)
		get_uv_map(line[4], &sphere->uv_color, list);
	if (count_arguments(line) >= 6)
		get_bump_map(line[5], &sphere->bump, list);
	return (0);
}

int	new_sphere_struct(t_scene *scene, char **line)
{
	t_sphere	*sphere;
	t_object	*object;

	sphere = ft_calloc(1, sizeof(t_sphere));
	if (sphere == NULL)
		return (printf("Error\nMalloc fail\n"), 2);
	if (fill_sphere_struct(sphere, line, scene->textures) != 0)
		return (free(sphere), 1);
	object = ft_calloc(1, sizeof(t_object));
	if (object == NULL)
		return (free (sphere), printf("Error\nMalloc fail\n"), 2);
	object->type = SPHERE;
	object->data = sphere;
	object->is_hit = (int (*)(t_ray *, void *))is_hit_sphere;
	object->get_hit_dist = (float (*)(t_ray *, void *))get_hit_dist_sphere;
	object->get_hit_data = (void (*)(t_ray *, void *, t_scene *))
		get_hit_data_sphere;
	add_object_to_back(&(scene->objects), object);
	return (0);
}
