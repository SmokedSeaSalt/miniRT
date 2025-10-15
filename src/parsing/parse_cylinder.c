/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:00:29 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/15 14:16:25 by mvan-rij         ###   ########.fr       */
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

static int	fill_top_endcap_struct(t_scene *scene, t_cylinder *cylinder)
{
	t_endcap	*endcap_top;
	t_object	*object;

	endcap_top = ft_calloc(1, sizeof(t_endcap));
	if (endcap_top == NULL)
		return (printf("Malloc fail\n"), 2);
	endcap_top->color = cylinder->color;
	endcap_top->diameter = cylinder->diameter;
	endcap_top->radius = cylinder->radius;
	endcap_top->orientation = cylinder->orientation;
	endcap_top->coords.v = (cylinder->coords.v + \
(cylinder->orientation.v * cylinder->height * 0.5));
	object = ft_calloc(1, sizeof(t_object));
	if (object == NULL)
		return (free (endcap_top), printf("Malloc fail\n"), 2);
	object->type = ENDCAP;
	object->data = endcap_top;
	object->is_hit = (int (*)(t_ray *, void *))is_hit_endcap;
	object->get_hit_dist = NULL;
	object->get_hit_data = NULL;
	add_object_to_back(&(scene->objects), object);
	return (0);
}

static int	fill_bottom_endcap_struct(t_scene *scene, t_cylinder *cylinder)
{
	t_endcap	*endcap_bottom;
	t_object	*object;

	endcap_bottom = ft_calloc(1, sizeof(t_endcap));
	if (endcap_bottom == NULL)
		return (printf("Malloc fail\n"), 2);
	endcap_bottom->color = cylinder->color;
	endcap_bottom->diameter = cylinder->diameter;
	endcap_bottom->radius = cylinder->radius;
	endcap_bottom->orientation.v = -cylinder->orientation.v;
	endcap_bottom->coords.v = (cylinder->coords.v + \
(cylinder->orientation.v * cylinder->height * -0.5));
	object = ft_calloc(1, sizeof(t_object));
	if (object == NULL)
		return (free (endcap_bottom), printf("Malloc fail\n"), 2);
	object->type = ENDCAP;
	object->data = endcap_bottom;
	object->is_hit = (int (*)(t_ray *, void *))is_hit_endcap;
	object->get_hit_dist = NULL;
	object->get_hit_data = NULL;
	add_object_to_back(&(scene->objects), object);
	return (0);
}

static int	new_endcap_struct(t_scene *scene, t_cylinder *cylinder)
{
	if (fill_top_endcap_struct(scene, cylinder) != 0)
		return (1);
	if (fill_bottom_endcap_struct(scene, cylinder) != 0)
		return (1);
	return (0);
}

static int	fill_cylinder_struct(t_cylinder *cylinder, char **line)
{
	if (count_arguments(line) != 12)
		return (printf("Cylinder: Incorrect amount of arguments\n"), 1);
	cylinder->coords = fill_vec3(line[1], line[2], line[3]);
	cylinder->orientation = fill_vec3(line[4], line[5], line[6]);
	if (orientation_out_of_range(cylinder->orientation))
		return (printf("Cylinder: Orientation out of range\n"), 1);
	if (orientation_all_zero(cylinder->orientation))
		return (printf("Cylinder: Orientation can not be all zero\n"), 1);
	cylinder->orientation = vec3_normalize(cylinder->orientation);
	cylinder->diameter = ft_atof(line[7]);
	if (cylinder->diameter < 0.0f)
		return (printf("Cylinder: Negative diameter not allowed"));
	cylinder->radius = cylinder->diameter * 0.5f;
	cylinder->height = ft_atof(line[8]);
	if (cylinder->diameter < 0.0f)
		return (printf("Cylinder: Negative height not allowed"));
	cylinder->color = fill_color(line[9], line[10], line[11]);
	if (color_out_of_range(cylinder->color))
		return (printf("Cylinder: Color out of range\n"), 1);
	return (0);
}

int	new_cylinder_struct(t_scene *scene, char **line)
{
	t_cylinder	*cylinder;
	t_object	*object;

	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (cylinder == NULL)
		return (printf("Malloc fail\n"), 2);
	if (fill_cylinder_struct(cylinder, line) != 0)
		return (free(cylinder), 1);
	object = ft_calloc(1, sizeof(t_object));
	if (object == NULL)
		return (free (cylinder), printf("Malloc fail\n"), 2);
	object->type = CYLINDER;
	object->data = cylinder;
	object->is_hit = (int (*)(t_ray *, void *))is_hit_cylinder;
	object->get_hit_dist = (float (*)(t_ray *, void *))get_hit_dist_cylinder;
	object->get_hit_data = (void (*)(t_ray *, void *, t_scene *))get_hit_data_cylinder;
	add_object_to_back(&(scene->objects), object);
	if (new_endcap_struct(scene, cylinder) != 0)
		return (1);
	return (0);
}
