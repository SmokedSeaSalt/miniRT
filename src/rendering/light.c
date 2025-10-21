/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:27:34 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/21 15:54:04 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"
#include "consts.h"

//should we ignore the object were comming from because it could couse issues because ray starts on that surface?
//could also have issues if we are for example inside a sphere. then we might see light outside the sphere.
//to fix this add small ofset to light ray in direction of surface normal and still compare with self?
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

void	add_single_light_result(t_scene *scene, t_lights *light, t_ray *ray)
{
	t_ray	light_ray;
	float	light_dist;
	float	light_lambertian;

	light_ray.orig.v = ray->orig.v + (ray->vec3.v * ray->results.hit_dist);
	light_ray.vec3.v = light->coords.v - light_ray.orig.v;
	light_dist = vec3_length(light_ray.vec3);
	light_ray.vec3 = vec3_normalize(light_ray.vec3);

	//fist cheap is bigger than 90 check, then brightness from light = 0 so we can skip looping linked list of objects.
	if (!(is_vec3_angle_acute(&ray->results.hit_normal, &light_ray.vec3) == 0 || \
is_light_obstructed(scene->objects, &light_ray, light_dist, ray->results.object) == 1))
	{
		light_lambertian = vec3_dot(light_ray.vec3, ray->results.hit_normal);
		ray->results.light_intensity.r += (light->color_brightness.r * light_lambertian);
		ray->results.light_intensity.g += (light->color_brightness.g * light_lambertian);
		ray->results.light_intensity.b += (light->color_brightness.b * light_lambertian);
	}
}

void	set_light_hit_angle_and_intensity(t_scene *scene, t_ray *ray)
{
	t_lights *current_light;

	current_light = scene->lights;
	while (current_light != NULL)
	{
		add_single_light_result(scene, current_light, ray);
		current_light = current_light->next;
	}
}
