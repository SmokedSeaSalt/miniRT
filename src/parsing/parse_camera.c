/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 11:59:04 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/11/04 14:24:23 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>		//to use free
#include <stdio.h>		//to use printf
#include "parsing.h"
#include "helpers.h"
#include "libft.h"
#include "structs.h"
#include "math_inc.h"
#include "consts.h"

static int	fill_camera_struct(t_camera *camera, char **line)
{
	if (count_arguments(line) != 4)
		return (printf("Error\nCamera: "N_ARGS_ERR"\n"), 1);
	if (parse_orig(&(camera->coords), line[1]) != 0)
		return (printf("Camera: Origin parsing error\n"), 1);
	if (parse_normal_vector(&(camera->orientation), line[2]) != 0)
		return (printf("Camera: Orientation parsing error\n"), 1);
	if (parse_fov(&(camera->fov_rad), line[3]) != 0)
		return (printf("Camera: Fov parsing error\n"), 1);
	return (0);
}

int	new_camera_struct(t_scene *scene, char **line)
{
	t_camera	*camera;

	if (scene->camera != NULL)
		return (printf("Error\nCamera: "N_ELEMENTS_ERR"\n"), 1);
	camera = ft_calloc(1, sizeof(t_camera));
	if (camera == NULL)
		return (printf("Error\nMalloc fail\n"), 2);
	if (fill_camera_struct(camera, line) != 0)
		return (free(camera), 1);
	scene->camera = camera;
	return (0);
}
