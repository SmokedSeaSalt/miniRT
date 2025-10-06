/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:57:43 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/06 17:02:46 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <float.h>
#include <math.h>
#include "structs.h"
#include "math_inc.h"
#include "rendering.h"

void	loop_though_objects(t_ray *ray, t_object *object_list)
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
		ray->results.object->get_hit_data(ray, ray->results.object->data);
}


void render_pixel(int x, int y, t_scene *scene)
{
	t_ray ray;
	int r;
	int g;
	int b;
	int colour;

	ray = get_ray(x, y ,scene->camera);
	loop_though_objects(&ray, scene->objects);
	if (ray.results.is_hit == 0)
		mlx_put_pixel(scene->g_img, x, y, 0x000000ff);
	else
	{
		r = (int)(0.5f * (ray.results.normal_at.x + 1) * 0xff);
		g = (int)(0.5f * (ray.results.normal_at.y + 1) * 0xff);
		b = (int)(0.5f * (ray.results.normal_at.z + 1) * 0xff);
		//r = (int)(fabs(ray.results.normal_at.x) * 0xff);
		//g = (int)(fabs(ray.results.normal_at.y) * 0xff);
		//b = (int)(fabs(ray.results.normal_at.z) * 0xff);
		colour = (r << 3*8) + (g << 2*8) + (b << 1*8) + 0xff;
		mlx_put_pixel(scene->g_img, x, y, colour);
	}
}

int	render(t_scene *scene)
{
	int i_x;
	int i_y;

	i_x = 0;
	while (i_x < scene->camera->window_info.height)
	{
		i_y = 0;
		while (i_y < scene->camera->window_info.width)
		{
			render_pixel(i_x, i_y, scene);
			i_y++;
		}

		i_x++;
	}



	return (0);
}