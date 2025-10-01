/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:59:04 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/01 17:00:26 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>		//to use free
#include <stdio.h>		//to use printf
#include "parsing.h"
#include "helpers.h"
#include "libft.h"
#include "structs.h"
#include "math_inc.h"

static int	fill_camera_struct(t_camera *camera, char **line)
{
	if (count_arguments(line) != 8)
		return (printf("Camera: Incorrect amount of arguments\n"), 1);
	camera->coords = fill_vec3(line[1], line[2], line[3]);
	camera->orientation = fill_vec3(line[4], line[5], line[6]);
	if (orientation_out_of_range(camera->orientation))
		return (printf("Camera: Orientation out of range\n"), 1);
	if (orientation_all_zero(camera->orientation))
		return (printf("Camera: Orientation can not be all zero\n"), 1);
	camera->orientation = vec3_normalize(camera->orientation);
	camera->fov = ft_atoi(line[7]);
	if (camera->fov < 0 || camera->fov > 180)
		return (printf("Camera: FOV out of range\n"), 1);
	return (0);
}

int	new_camera_struct(t_scene *scene, char **line)
{
	t_camera	*camera;

	if (scene->camera != NULL)
		return (printf("Camera: Does not support multiple elements\n"), 1);
	camera = ft_calloc(1, sizeof(t_camera));
	if (camera == NULL)
		return (printf("Malloc fail\n"), 2);
	if (fill_camera_struct(camera, line) != 0)
		return (free(camera), 1);
	scene->camera = camera;
	return (0);
}
