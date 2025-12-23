/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:00:29 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/23 16:22:59 by mvan-rij         ###   ########.fr       */
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

static int	fill_top_endcap_struct(t_scene *scene, t_cylinder *cylinder)
{
	t_endcap	*endcap_top;
	t_object	*object;

	endcap_top = ft_calloc(1, sizeof(t_endcap));
	if (endcap_top == NULL)
		return (printf("Error\nMalloc fail\n"), 2);
	endcap_top->color = cylinder->color;
	endcap_top->diameter = cylinder->diameter;
	endcap_top->radius = cylinder->radius;
	endcap_top->normal = cylinder->orientation;
	endcap_top->coords.v = (cylinder->coords.v + \
(cylinder->orientation.v * cylinder->height * 0.5));
	endcap_top->uv_color = cylinder->uv_color;
	endcap_top->bump = cylinder->bump;
	object = ft_calloc(1, sizeof(t_object));
	if (object == NULL)
		return (free (endcap_top), printf("Error\nMalloc fail\n"), 2);
	object->type = ENDCAPTOP;
	object->data = endcap_top;
	object->is_hit = (int (*)(t_ray *, void *))is_hit_endcap;
	object->get_hit_dist = (float (*)(t_ray *, void *))get_hit_dist_endcap;
	object->get_hit_data = (void (*)(t_ray *, void *, t_scene *))
		get_hit_data_endcap;
	add_object_to_back(&(scene->objects), object);
	return (0);
}

static int	fill_bottom_endcap_struct(t_scene *scene, t_cylinder *cylinder)
{
	t_endcap	*endcap_bottom;
	t_object	*object;

	endcap_bottom = ft_calloc(1, sizeof(t_endcap));
	if (endcap_bottom == NULL)
		return (printf("Error\nMalloc fail\n"), 2);
	endcap_bottom->color = cylinder->color;
	endcap_bottom->diameter = cylinder->diameter;
	endcap_bottom->radius = cylinder->radius;
	endcap_bottom->normal.v = -cylinder->orientation.v;
	endcap_bottom->coords.v = (cylinder->coords.v + \
(cylinder->orientation.v * cylinder->height * -0.5f));
	endcap_bottom->uv_color = cylinder->uv_color;
	endcap_bottom->bump = cylinder->bump;
	object = ft_calloc(1, sizeof(t_object));
	if (object == NULL)
		return (free (endcap_bottom), printf("Error\nMalloc fail\n"), 2);
	object->type = ENDCAPBOT;
	object->data = endcap_bottom;
	object->is_hit = (int (*)(t_ray *, void *))is_hit_endcap;
	object->get_hit_dist = (float (*)(t_ray *, void *))get_hit_dist_endcap;
	object->get_hit_data = (void (*)(t_ray *, void *, t_scene *))
		get_hit_data_endcap;
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

static int	fill_cylinder_struct(t_cylinder *cylinder, char **line,
		t_texture_list *list)
{
	if (count_arguments(line) < 6 || count_arguments(line) > 8)
		return (printf("Error\nCylinder: Incorrect amount of arguments\n"), 1);
	if (parse_orig(&(cylinder->coords), line[1]) != 0)
		return (printf("Cylinder: Origin parsing error\n"), 1);
	if (parse_normal_vector(&(cylinder->orientation), line[2]) != 0)
		return (printf("Cylinder: Orientation parsing error\n"), 1);
	cylinder->diameter = fabs(ft_atof(line[3]));
	cylinder->radius = cylinder->diameter * 0.5f;
	cylinder->height = fabs(ft_atof(line[4]));
	if (parse_color(&(cylinder->color), line[5]) != 0)
		return (printf("Cylinder: Color parsing error\n"), 1);
	if (count_arguments(line) >= 7)
		get_uv_map(line[6], &cylinder->uv_color, list);
	if (count_arguments(line) >= 8)
		get_bump_map(line[7], &cylinder->bump, list);
	return (0);
}

int	new_cylinder_struct(t_scene *scene, char **line)
{
	t_cylinder	*cylinder;
	t_object	*object;

	cylinder = ft_calloc(1, sizeof(t_cylinder));
	if (cylinder == NULL)
		return (printf("Error\nMalloc fail\n"), 2);
	if (fill_cylinder_struct(cylinder, line, scene->textures) != 0)
		return (free(cylinder), 1);
	object = ft_calloc(1, sizeof(t_object));
	if (object == NULL)
		return (free (cylinder), printf("Error\nMalloc fail\n"), 2);
	object->type = CYLINDER;
	object->data = cylinder;
	object->is_hit = (int (*)(t_ray *, void *))is_hit_cylinder;
	object->get_hit_dist = (float (*)(t_ray *, void *))get_hit_dist_cylinder;
	object->get_hit_data = (void (*)(t_ray *, void *, t_scene *))
		get_hit_data_cylinder;
	add_object_to_back(&(scene->objects), object);
	if (new_endcap_struct(scene, cylinder) != 0)
		return (1);
	return (0);
}
