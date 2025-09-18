/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:09:54 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/18 17:07:18 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "helpers.h"
#include "parsing.h"
#include "libft.h"

//TODO
//add checking for multiple where only one may exist
//error handling
//make unit tests

int	fill_ambient_struct(t_ambient *ambient, char **line)
{
	if (count_arguments(line) != 5)
		return (printf("Ambient: Incorrect amount of arguments"), 1);
	ambient->ratio = ft_atof(line[1]);
	if (ambient->ratio < 0.0 || ambient->ratio > 1.0)
		return (printf("Ambient: Ratio out of range"), 1);
	ambient->color = fill_color(line[2], line[3], line[4]);
	if (color_out_of_range(ambient->color))
		return (printf("Ambient: Color out of range"), 1);
	return (0);
}

int	fill_camera_struct(t_camera *camera, char **line)
{
	if (count_arguments(line) != 8)
		return (printf("Camera: Incorrect amount of arguments"), 1);
	camera->coords = fill_vec3(line[1], line[2], line[3]);
	camera->orientation = fill_vec3(line[4], line[5], line[6]);
	if (orientation_out_of_range(camera->orientation))
		return (printf("Camera: Orientation out of range"), 1);
	if (orientation_all_zero(camera->orientation))
		return (printf("Camera: Orientation can not be all zero"), 1);
	camera->orientation = normalize_vec3(camera->orientation);
	camera->fov = ft_atoi(line[7]);
	if (camera->fov < 0 || camera->fov > 180)
		return (printf("Camera: FOV out of range"), 1);
	return (0);
}

int	fill_light_struct(t_light *light, char **line)
{
	if (count_arguments(line) != 8)
		return (printf("Light: Incorrect amount of arguments"), 1);
	light->coords = fill_vec3(line[1], line[2], line[3]);
	light->brightness = ft_atof(line[4]);
	if (light->brightness < 0.0 || light->brightness > 1.0)
		return (printf("Light: Brightness out of range"), 1);
	light->color = fill_color(line[5], line[6], line[7]);
	if (color_out_of_range(light->color))
		return (printf("Light: Color out of range"), 1);
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

int	fill_cylinder_struct(t_cylinder *cylinder, char **line)
{
	if (count_arguments(line) != 12)
		return (printf("Cylinder: Incorrect amount of arguments"), 1);
	cylinder->coords = fill_vec3(line[1], line[2], line[3]);
	cylinder->orientation = fill_vec3(line[4], line[5], line[6]);
	if (orientation_out_of_range(cylinder->orientation))
		return (printf("Cylinder: Orientation out of range"), 1);
	if (orientation_all_zero(cylinder->orientation))
		return (printf("Cylinder: Orientation can not be all zero"), 1);
	if (orientation_all_zero(cylinder->orientation))
		return (printf("Cylinder: Orientation can not be all zero"), 1);
	cylinder->orientation = normalize_vec3(cylinder->orientation);
	cylinder->diameter = ft_atoi(line[7]);
	cylinder->height = ft_atoi(line[8]);
	cylinder->color = fill_color(line[9], line[10], line[11]);
	if (color_out_of_range(cylinder->color))
		return (printf("Cylinder: Color out of range"), 1);
	return (0);
}
