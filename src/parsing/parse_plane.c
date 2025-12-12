/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:59:50 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/12 12:14:05 by mvan-rij         ###   ########.fr       */
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

static int	fill_plane_struct(t_plane *plane, char **line)
{
	if (count_arguments(line) < 4 || count_arguments(line) > 6)
		return (printf("Error\nPlane: Incorrect amount of arguments\n"), 1);
	if (parse_orig(&(plane->coords), line[1]) != 0)
		return (printf("Plane: Origin parsing error\n"), 1);
	if (parse_normal_vector(&(plane->normal), line[2]) != 0)
		return (printf("Plane: Vector parsing error\n"), 1);
	if (parse_color(&(plane->color), line[3]) != 0)
		return (printf("Plane: Color parsing error\n"), 1);
	if (count_arguments(line) >= 5)
		plane->uv_color = get_uv_map(line[4]);
	if (count_arguments(line) >= 6)
		plane->bump = get_bump_map(line[5]);
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
