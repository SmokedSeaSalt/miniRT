/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:57:43 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/21 16:53:58 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_inc.h"
#include "rendering.h"
#include "structs.h"
#include <float.h>

/// @brief loop trough all object to check what object needs to be rendered.
/// @param scene
/// @param ray
/// @param object_list
void	loop_though_objects(t_scene *scene, t_ray *ray, t_object *object_list)
{
	int						is_hit;
	float					hit_dist;

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
		ray->results.object->get_hit_data(ray, ray->results.object->data, scene);
}

/// @brief render single pixel.
/// @param x
/// @param y
/// @param scene
void	render_pixel(int x, int y, t_scene *scene)
{
	t_ray	ray;

	ray = get_ray(x, y, scene->camera);
	loop_though_objects(scene, &ray, scene->objects);
	if (ray.results.is_hit == 0)
		scene->render_info.render_miss(&ray, x, y, scene);
	else
		scene->render_info.render_hit(&ray, x, y, scene);
}

/// @brief loop through all pixels and render the values.
/// @param scene
/// @return
int	render_frame(t_scene *scene)
{
	int	i_x;
	int	i_y;

	i_x = 0;
	while (i_x < scene->camera->window_info.width)
	{
		i_y = 0;
		while (i_y < scene->camera->window_info.height)
		{
			render_pixel(i_x, i_y, scene);
			i_y++;
		}
		i_x++;
	}
	return (0); //change to void?
}
