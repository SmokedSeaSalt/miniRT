/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:27:34 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/09 12:17:38 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"
#include "consts.h"
#include "stdio.h"

// float	angle_between_ray_and_light(t_ray *ray, t_light *light)
// {
// 	return (get_angle_between_vec3(&ray->orig, &light->coords));
// }

//should we ignore the object were comming from because it could couse issues because ray starts on that surface?
int	is_light_obstructed(t_object *object_list, t_ray *light_ray, float light_dist, t_object *self)
{
	float	hit_dist;
	int		is_hit;

	while (object_list != NULL)
	{
		is_hit = object_list->is_hit(light_ray, object_list->data);
		if (is_hit == 1 && object_list != self)
		{
			hit_dist = object_list->get_hit_dist(light_ray, object_list->data);
			if (hit_dist > 0.0f && hit_dist < light_dist)
				return (1);
		}
		object_list = object_list->next;
	}
	return (0);
}

void	set_light_hit_angle_and_intensity(t_scene *scene, t_ray *ray)
{
	t_ray	light_ray;
	float	light_dist;

	light_ray.orig.v = ray->orig.v + (ray->vec3.v * ray->results.hit_dist);
	light_ray.vec3.v = scene->light->coords.v - light_ray.orig.v;
	light_dist = vec3_length(light_ray.vec3);
	light_ray.vec3 = vec3_normalize(light_ray.vec3);

	//fist cheap is bigger than 90 check, then brightness from light = 0 so we can skip looping linked list of objects.
	if (is_vec3_angle_acute(&ray->results.hit_normal, &light_ray.vec3) == 0 || \
is_light_obstructed(scene->objects, &light_ray, light_dist, ray->results.object) == 1)
	{
		ray->results.light_angle = -1.0f;
		ray->results.light_intensity = 0;
		return ;
	}
	else
	{
		// todo optimization: maybe no need to calculate exact theta and
		// instead can deal with cos(theta) for an estimation for intensity
		ray->results.light_angle = get_angle_between_vec3(&ray->results.hit_normal, &light_ray.vec3);
		ray->results.light_intensity = 1.0f - (ray->results.light_angle / PI);
	}
}
