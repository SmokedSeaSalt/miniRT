/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 14:58:50 by mvan-rij          #+#    #+#             */
/*   Updated: 2026/01/02 14:07:45 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "rendering.h"
#include <float.h>

/// @brief loop trough all object to check what object needs to be rendered.
/// @param scene
/// @param ray
/// @param object_list
void	loop_though_objects(t_scene *scene, t_ray *ray, t_object *object_list)
{
	int		is_hit;
	float	hit_dist;

	ray->results.hit_dist = FLT_MAX;
	while (object_list != NULL)
	{
		is_hit = object_list->is_hit(ray, object_list->data);
		if (is_hit == 1)
		{
			hit_dist = object_list->get_hit_dist(ray, object_list->data);
			if (hit_dist > 0.0f && hit_dist < ray->results.hit_dist)
			{
				ray->results.is_hit = 1;
				ray->results.hit_dist = hit_dist;
				ray->results.object = object_list;
			}
		}
		object_list = object_list->next;
	}
	if (ray->results.is_hit == 1)
		ray->results.object->get_hit_data(ray, \
ray->results.object->data, scene);
}

/// @brief render single pixel.
/// @param x
/// @param y
/// @param scene
void	render_pixel(int x, int y, t_scene *scene)
{
	t_ray	ray;

	ray = get_ray(x, y, scene->camera, &(scene->window_info));
	loop_though_objects(scene, &ray, scene->objects);
	if (ray.results.is_hit == 0)
		scene->render_info.render_miss(&ray, x, y, scene);
	else
		scene->render_info.render_hit(&ray, x, y, scene);
}
