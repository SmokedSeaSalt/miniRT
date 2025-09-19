/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:59:33 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/19 12:40:49 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "helpers.h"
#include "libft.h"
#include "structs.h"

int	new_sphere_struct(t_scene *scene, char **line)
{
	t_sphere	*sphere;

	if (sphere != NULL)
		return (printf("Sphere: Does not support multiple elements"), 1);
	sphere = ft_calloc(1, sizeof(t_sphere));
	if (sphere == NULL)
		return (printf("Malloc fail"), 2);
	if (fill_sphere_struct(sphere, line) != 0)
		return (free(amient), 1);
	// scene->object = sphere; todo add to back of obj list
	return (0);
}

int	fill_sphere_struct(t_sphere *sphere, char **line)
{
	if (count_arguments(line) != 8)
		return (printf("Sphere: Incorrect amount of arguments"), 1);
	sphere->coords = fill_vec3(line[1], line[2], line[3]);
	sphere->diameter = ft_atof(line[4]);
	sphere->color = fill_color(line[5], line[6], line[7]);
	if (color_out_of_range(sphere->color))
		return (printf("Sphere: Color out of range"), 1);
	return (0);
}
