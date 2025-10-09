/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:27:34 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/09 09:37:13 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"
#include "consts.h"

// float	angle_between_ray_and_light(t_ray *ray, t_light *light)
// {
// 	return (get_angle_between_vec3(&ray->orig, &light->coords));
// }

// reused code in loop_through_obects? or is it different because this one stops
// at a single hit?
int	is_light_obstructed(t_scene *scene, t_ray *ray, t_ray *hit_to_camera_ray)
{
	float		hit_to_camera_dist;
	float		cur_hit_dist;
	t_object	*object_list;

	hit_to_camera_dist = vec3_length(hit_to_camera_ray->vec3);
	object_list = scene->objects;
	while (object_list)
	{
		// should use t_ray for hit_to_camera_ray so that we can reuse
		// get_hit_dist?
		cur_hit_dist = object_list->get_hit_dist(ray, object_list);
		if (cur_hit_dist > 0 && cur_hit_dist < hit_to_camera_dist)
			return (1);
		object_list = object_list->next;
	}
	return (0);
}

void	set_light_hit_angle_and_intensity(t_scene *scene, t_ray *ray)
{
	t_vec3	hit_point;
	t_ray	hit_to_camera_ray;
	
	hit_point.v = ray->orig.v + (ray->vec3.v * ray->results.hit_dist);
	
	hit_to_camera_ray.vec3.v = scene->camera->coords.v - hit_point.v;
	hit_to_camera_ray.orig = hit_point;
	
	if (is_light_obstructed(scene, ray, &hit_to_camera_ray) == 1)
	{
		ray->results.light_angle = -1.0f;
		ray->results.light_intensity = scene->ambient->ratio; //todo add ambient. also color should be added to t_results? we need to add ambient color and intensity
	}
	else
	{
		// todo optimization: maybe no need to calculate exact theta and 
		// instead can deal with cos(theta) for an estimation for intensity
		ray->results.light_angle = get_angle_between_vec3(&ray->vec3, &hit_to_camera_ray.vec3);
		ray->results.light_intensity = 1.0f - (ray->results.light_angle / PI);
		ray->results.light_intensity += scene->ambient->ratio; // todo add ambient
	}
}