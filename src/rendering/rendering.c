/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:57:43 by egrisel           #+#    #+#             */
/*   Updated: 2025/11/06 11:00:40 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_inc.h"
#include "rendering.h"
#include "structs.h"
#include <float.h>
#include <math.h>

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
		ray->results.object->get_hit_data(ray, ray->results.object->data, scene);
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

void render_block(int x, int y, t_scene *scene)
{
	t_ray	ray;
	int block_size;
	int	i_x;
	int	i_y;

	block_size = powf(2, scene->window_info.render_depth);
	ray = get_ray(x, y, scene->camera, &(scene->window_info));
	loop_though_objects(scene, &ray, scene->objects);

	i_x = x;
	while (i_x < (x + block_size) && i_x < scene->window_info.width)
	{
		i_y = y;
		while (i_y < (y + block_size) && i_y < scene->window_info.height)
		{
			if (ray.results.is_hit == 0)
				scene->render_info.render_miss(&ray, i_x, i_y, scene);
			else
				scene->render_info.render_hit(&ray, i_x, i_y, scene);
			i_y++;
		}
		i_x++;
	}
}

int block_already_rendered(int x, int y, t_window_info *window_info)
{
	int higher_block_size;
	int depth_check;

	if (window_info->max_render_depth == window_info->render_depth)
			return (0);
	depth_check = window_info->render_depth + 1;
	higher_block_size = pow(2, depth_check);
	if (x % higher_block_size == 0 && y % higher_block_size == 0)
		return (1);
	return (0);
}

//calculate max depth
//any key press sets current depth back to max depth
void render_frame(t_scene *scene)
{
	int	i_x;
	int block_size;

	if (scene->window_info.render_depth < 0)
		return ;
	block_size = pow(2, scene->window_info.render_depth);
	i_x = 0;
	while (i_x < scene->window_info.width)
	{
		if (block_already_rendered(i_x, scene->window_info.render_y, \
&(scene->window_info)) == 0)
			render_block(i_x, scene->window_info.render_y, scene);
		i_x += block_size;
	}
	scene->window_info.render_y += block_size;
	if (scene->window_info.render_y >= scene->window_info.height)
	{
		scene->window_info.render_y = 0;
		(scene->window_info.render_depth)--;
	}
}
