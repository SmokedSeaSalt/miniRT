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
//normalize orientation -> full vector3 scale to -1,1
//check orientation not all 0
//add checking for multiple where only one may exist
//error handling

int	fill_ambient_struct(t_ambient *ambient, char **line)
{
	if (count_arguments(line) != 5)
		return (printf("Ambient: Incorrect amount of arguments"), 1);
	ambient->ratio = ft_atof(line[1]);
	if (ambient->ratio < 0.0 || ambient->ratio > 1.0)
		return (printf("Ambient: Ratio out of range"), 1);
	ambient->color.r = ft_atoi(line[2]);
	ambient->color.g = ft_atoi(line[3]);
	ambient->color.b = ft_atoi(line[4]);
	if (color_out_of_range(ambient->color))
		return (printf("Ambient: Color out of range"), 1);
	return (0);
}

int	fill_camera_struct(t_camera *camera, char **line)
{
	if (count_arguments(line) != 8)
		return (printf("Camera: Incorrect amount of arguments"), 1);
	camera->coords.x = ft_atof(line[1]);
	camera->coords.y = ft_atof(line[2]);
	camera->coords.z = ft_atof(line[3]);
	camera->orientation.x = ft_atof(line[4]);
	camera->orientation.y = ft_atof(line[5]);
	camera->orientation.z = ft_atof(line[6]);
	if (orientation_out_of_range(camera->orientation))
		return (printf("Camera: Orientation out of range"), 1);
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
	light->coords.x = ft_atof(line[1]);
	light->coords.y = ft_atof(line[2]);
	light->coords.z = ft_atof(line[3]);
	light->brightness = ft_atof(line[4]);
	if (light->brightness < 0.0 || light->brightness > 1.0)
		return (printf("Light: Brightness out of range"), 1);
	light->color.r = ft_atoi(line[5]);
	light->color.g = ft_atoi(line[6]);
	light->color.b = ft_atoi(line[7]);
	if (color_out_of_range(light->color))
		return (printf("Light: Color out of range"), 1);
	return (0);
}

int	fill_sphere_struct(t_sphere *sphere, char **line)
{
	if (count_arguments(line) != 8)
		return (printf("Sphere: Incorrect amount of arguments"), 1);
	sphere->coords.x = ft_atof(line[1]);
	sphere->coords.y = ft_atof(line[2]);
	sphere->coords.z = ft_atof(line[3]);
	sphere->diameter = ft_atof(line[4]);
	sphere->color.r = ft_atoi(line[5]);
	sphere->color.g = ft_atoi(line[6]);
	sphere->color.b = ft_atoi(line[7]);
	if (color_out_of_range(sphere->color))
		return (printf("Sphere: Color out of range"), 1);
	return (0);
}

int	fill_plane_struct(t_plane *plane, char **line)
{
	if (count_arguments(line) != 10)
		return (printf("Plane: Incorrect amount of arguments"), 1);
	plane->coords.x = ft_atof(line[1]);
	plane->coords.y = ft_atof(line[2]);
	plane->coords.z = ft_atof(line[3]);
	plane->orientation.x = ft_atof(line[4]);
	plane->orientation.y = ft_atof(line[5]);
	plane->orientation.z = ft_atof(line[6]);
	if (orientation_out_of_range(plane->orientation))
		return (printf("Plane: Orientation out of range"), 1);
	plane->orientation = normalize_vec3(plane->orientation);
	plane->color.r = ft_atoi(line[7]);
	plane->color.g = ft_atoi(line[8]);
	plane->color.b = ft_atoi(line[9]);
	if (color_out_of_range(plane->color))
		return (printf("Plane: Color out of range"), 1);
	return (0);
}

int	fill_cylinder_struct(t_cylinder *cylinder, char **line)
{
	if (count_arguments(line) != 12)
		return (printf("Cylinder: Incorrect amount of arguments"), 1);
	cylinder->coords.x = ft_atof(line[1]);
	cylinder->coords.y = ft_atof(line[2]);
	cylinder->coords.z = ft_atof(line[3]);
	cylinder->orientation.x = ft_atof(line[4]);
	cylinder->orientation.y = ft_atof(line[5]);
	cylinder->orientation.z = ft_atof(line[6]);
	if (orientation_out_of_range(cylinder->orientation))
		return (printf("Cylinder: Orientation out of range"), 1);
	cylinder->orientation = normalize_vec3(cylinder->orientation);
	cylinder->diameter = ft_atoi(line[7]);
	cylinder->height = ft_atoi(line[8]);
	cylinder->color.r = ft_atoi(line[9]);
	cylinder->color.g = ft_atoi(line[10]);
	cylinder->color.b = ft_atoi(line[11]);
	if (color_out_of_range(plane->color))
		return (printf("Cylinder: Color out of range"), 1);
	return (0);
}
