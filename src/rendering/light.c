/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:27:34 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/31 14:41:14 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"
#include "consts.h"
#include <math.h>

//should we ignore the object were comming from because it could couse issues because ray starts on that surface?
//could also have issues if we are for example inside a sphere. then we might see light outside the sphere.
//to fix this add small ofset to light ray in direction of surface normal and still compare with self?

/// @brief loops trough the object list to check if any of the objects
/// @brief obstruct the current light_ray.
/// @param object_list
/// @param light_ray
/// @param light_dist
/// @param self
/// @return 1 if the light_ray is blocked by any object.
/// @return 0 if the light_ray is not blocked.
int	is_light_obstructed(t_object *object_list, t_ray light_ray, float light_dist, t_object *self)
{
	float	hit_dist;
	int		is_hit;

	(void)self;
	light_ray.orig.v = light_ray.orig.v + (0.0001f * light_ray.vec3.v);
	while (object_list != NULL)
	{
		is_hit = object_list->is_hit(&light_ray, object_list->data);
		if (is_hit == 1)
		{
			hit_dist = object_list->get_hit_dist(&light_ray, object_list->data);
			if (hit_dist > 0.0f && hit_dist < light_dist)
				return (1);
		}
		object_list = object_list->next;
	}
	return (0);
}

/// @brief calculates the ideal reflection angle for the light.
/// https://en.wikipedia.org/wiki/Phong_reflection_model
/// @param ray needs results.hit_normal to be known.
/// @param light_ray
/// @return the normalized reflection vector
t_vec3	light_reflection_angle(t_ray *ray, t_ray *light_ray)
{
	float	dot;
	t_vec3	angle;

	dot = vec3_dot(light_ray->vec3,ray->results.hit_normal);
	angle.v = 2 * dot * ray->results.hit_normal.v - light_ray->vec3.v;
	return (vec3_normalize(angle));
}

/// @brief calculates the specular reflection as per phong model.
/// https://en.wikipedia.org/wiki/Phong_reflection_model.
/// @param light
/// @param ray
/// @param light_ray
void	add_specular(t_lights *light, t_ray *ray, t_ray	*light_ray)
{
	t_vec3	reflection;
	float	dot;
	float	specular_intensity;
	float	exponent;

	exponent = 25.0f;
	reflection = light_reflection_angle(ray, light_ray);
	dot = fmax(0.0f, vec3_dot(reflection, (t_vec3)-ray->vec3.v));
	specular_intensity = powf(dot, exponent);
	ray->results.specular_intensity.r += (light->color_brightness.r * specular_intensity);
	ray->results.specular_intensity.g += (light->color_brightness.g * specular_intensity);
	ray->results.specular_intensity.b += (light->color_brightness.b * specular_intensity);
}

/// @brief calculates a single light intensity value and adds it to ray.results.
/// @param scene
/// @param light
/// @param ray
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
	//if (!(is_vec3_angle_acute(&ray->results.hit_normal, &light_ray.vec3)))
	//	return ;
	light_lambertian = vec3_dot(light_ray.vec3, ray->results.hit_normal);
	if (light_lambertian < 0.0f)
		return ;
	if (is_light_obstructed(scene->objects, light_ray, light_dist, ray->results.object) == 1)
		return ;
	ray->results.light_intensity.r += (light->color_brightness.r * light_lambertian);
	ray->results.light_intensity.g += (light->color_brightness.g * light_lambertian);
	ray->results.light_intensity.b += (light->color_brightness.b * light_lambertian);
	add_specular(light, ray, &light_ray);
}

/// @brief calculates a total light intensity value and adds it to ray.results.
/// @param scene
/// @param ray
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
