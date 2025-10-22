/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:59:50 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/22 15:05:48 by mvan-rij         ###   ########.fr       */
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

static int	fill_plane_struct(t_plane *plane, char **line)
{
	if (count_arguments(line) != 10)
		return (printf("Error\nPlane: Incorrect amount of arguments\n"), 1);
	plane->coords = fill_vec3(line[1], line[2], line[3]);
	plane->normal = fill_vec3(line[4], line[5], line[6]);
	if (orientation_out_of_range(plane->normal))
		return (printf("Error\nPlane: normal out of range\n"), 1);
	if (orientation_all_zero(plane->normal))
		return (printf("Error\nPlane: normal can not be all zero\n"), 1);
	plane->normal = vec3_normalize(plane->normal);
	plane->color = fill_color(line[7], line[8], line[9]);
	if (color_out_of_range(plane->color))
		return (printf("Error\nPlane: Color out of range\n"), 1);
	return (0);
}

int	new_plane_struct(t_scene *scene, char **line)
{
	t_plane		*plane;
	t_object	*object;

	plane = ft_calloc(1, sizeof(t_plane));
	if (plane == NULL)
		return (printf("Error\nMalloc fail\n"), 2);
	if (fill_plane_struct(plane, line) != 0)
		return (free(plane), 1);
	object = ft_calloc(1, sizeof(t_object));
	if (object == NULL)
		return (free (plane), printf("Error\nMalloc fail\n"), 2);
	object->type = PLANE;
	object->data = plane;
	object->is_hit = (int (*)(t_ray *, void *))is_hit_plane;
	object->get_hit_dist = (float (*)(t_ray *, void *))git_hit_dist_plane;
	object->get_hit_data = (void (*)(t_ray *, void *, t_scene *))get_hit_data_plane;
	add_object_to_back(&(scene->objects), object);
	return (0);
}
