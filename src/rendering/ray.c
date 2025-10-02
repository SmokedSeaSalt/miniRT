/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:23:02 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/02 11:31:25 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include "consts.h"
#include "math_inc.h"
#include "math.h" // for tan

/// delete
#include <stdio.h>

t_vec3	local_to_world(t_camera *camera, t_vec3 local_point_on_img_plane)
{
	(void)local_point_on_img_plane;
	(void)camera;
	return (local_point_on_img_plane);
}


// (1,1). 10x10

t_ray	*get_ray(int x, int y, t_camera *camera)
{
	t_vec3	local_point_on_img_plane;
	t_vec3	world_point_on_img_plane;
	t_ray	*ray;
	int		width;
	int		height;
	
	ray = ft_calloc(1, sizeof(t_ray));
	if (ray == NULL)
		return (NULL);
	width = camera->window_info.width;
	height = camera->window_info.height;
	local_point_on_img_plane.x = (2 * (((float)x + 0.5) / (float)width) - 1)\
* camera->window_info.aspect_ratio * camera->fov_scale;
	local_point_on_img_plane.y = (1 - 2 * (((float)y + 0.5)\
/ (float)height)) * camera->fov_scale;
	local_point_on_img_plane.z = -1.0f;
	world_point_on_img_plane = local_to_world(camera, local_point_on_img_plane);
	
	ray->vec3= local_point_on_img_plane;
	ray->vec3 = vec3_normalize(ray->vec3);
	ray->orig = camera->coords;
	return (ray);
}
