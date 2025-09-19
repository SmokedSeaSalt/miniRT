/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:59:50 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/19 12:44:39 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>		//to use printf
#include "helpers.h"
#include "libft.h"
#include "structs.h"

int	new_plane_struct(t_scene *scene, char **line)
{
	t_plane	*plane;

	if (plane != NULL)
		return (printf("Plane: Does not support multiple elements"), 1);
	plane = ft_calloc(1, sizeof(t_plane));
	if (plane == NULL)
		return (printf("Malloc fail"), 2);
	if (fill_plane_struct(plane, line) != 0)
		return (free(amient), 1);
	// scene->object = plane; todo add to back of obj list
	return (0);
}

int	fill_plane_struct(t_plane *plane, char **line)
{
	if (count_arguments(line) != 10)
		return (printf("Plane: Incorrect amount of arguments"), 1);
	plane->coords = fill_vec3(line[1], line[2], line[3]);
	plane->orientation = fill_vec3(line[4], line[5], line[6]);
	if (orientation_out_of_range(plane->orientation))
		return (printf("Plane: Orientation out of range"), 1);
	if (orientation_all_zero(plane->orientation))
		return (printf("Plane: Orientation can not be all zero"), 1);
	plane->orientation = normalize_vec3(plane->orientation);
	plane->color = fill_color(line[7], line[8], line[9]);
	if (color_out_of_range(plane->color))
		return (printf("Plane: Color out of range"), 1);
	return (0);
}
