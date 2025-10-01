/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 12:00:29 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/01 17:00:32 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>		//to use free
#include <stdio.h>		//to use printf
#include "parsing.h"
#include "helpers.h"
#include "libft.h"
#include "structs.h"
#include "math_inc.h"

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
	cylinder->height = ft_atof(line[8]);
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
	add_object_to_back(&(scene->objects), object);
	return (0);
}
