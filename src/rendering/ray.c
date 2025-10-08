/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:23:02 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/08 14:33:43 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include "consts.h"
#include "math_inc.h"
#include "math.h" // for tan

t_vec3	get_pixel_coordinate_to_world_vec3(t_vec3 pixel_coordinates,
										t_camera *camera)
{
	t_vec3	world_up;
	t_vec3	right;
	t_vec3	up;
	t_vec3	forward;
	t_vec3	world_vec3;

	forward = camera->orientation;
	world_up = vec3_new(0, 0, 1);
	if (fabs(forward.z) > 0.99f)
		world_up = vec3_new(1, 0, 0);
	right = vec3_normalize(vec3_cross(world_up, forward));
	up = vec3_normalize(vec3_cross(forward, right));
	world_vec3 = forward;
	world_vec3 = (t_vec3)(world_vec3.v + right.v * pixel_coordinates.x);
	world_vec3 = (t_vec3)(world_vec3.v + up.v * pixel_coordinates.y);
	world_vec3 = vec3_normalize(world_vec3);
	return (world_vec3);
}

t_vec3	get_pixel_coordinates(int x, int y, t_camera *camera)
{
	int		width;
	int		height;
	t_vec3	local_vec3;

	width = camera->window_info.width;
	height = camera->window_info.height;
	local_vec3.x = -1 * (2 * (((float)x + 0.5) / (float)width) - 1) \
* camera->window_info.aspect_ratio * camera->fov_scale;
	local_vec3.y = -1 * (2 * (((float)y + 0.5) / (float)height) - 1) \
* camera->fov_scale;
	local_vec3.z = -1.0f;
	return (local_vec3);
}

// maybe change vec3 to vec2
// change pixel coordinate name
t_ray	get_ray(int x, int y, t_camera *camera)
{
	t_vec3	pixel_coordinates;
	t_vec3	world_vec3;
	t_ray	ray;

	ft_bzero(&ray, sizeof (t_ray));
	pixel_coordinates = get_pixel_coordinates(x, y, camera);
	world_vec3 = get_pixel_coordinate_to_world_vec3(pixel_coordinates, camera);
	// ray.vec3 = local_direction;
	ray.vec3 = world_vec3;
	ray.orig = camera->coords;
	return (ray);
}
