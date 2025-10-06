/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 09:57:43 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/06 11:19:43 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"
#include "rendering.h"



void	calculate_sphere_hit(t_ray *ray, t_sphere *sphere)
{
	float disc;

	//todo sometime later: add the check for hit behind vector to set is_hit 0
	disc = sphere_intersects(*ray, *sphere);
	if (ray->results.is_hit == 0)
	{
		if (disc < 0)
		ray->results.is_hit = 0;
		else
		ray->results.is_hit = 1;
	}
}

void	loop_though_objects(t_ray *ray, t_object *object_list)
{

	while (object_list != NULL)
	{
		if (object_list->type == SPHERE)
			calculate_sphere_hit(ray, object_list->data);
		// if (object_list->type == PLANE)

		// if (object_list->type == CYLINDER)


		object_list = object_list->next;
	}
}

//void	loop_though_objects(t_ray *ray, t_object *object_list)
//{
//	int is_hit;
//	float hit_dist;

//	while (object_list != NULL)
//	{
//		is_hit = object_list.is_hit();
//		if ( is_hit == 1)
//		{
//			hit_dist = object_list.get_dist();
//			if (hit_dist < ray->results.hit_dist);
//				ray->results.obj = object_list;
//		}
//		object_list = object_list->next;
//	}
//	ray->results.obj.get_result_data;

//}


void render_pixel(int x, int y, t_scene *scene)
{
	t_ray ray;

	ray = get_ray(x, y ,scene->camera);
	loop_though_objects(&ray, scene->objects);
	if (ray.results.is_hit == 0)
		mlx_put_pixel(scene->g_img, x, y, 0x000000ff);
	else
		mlx_put_pixel(scene->g_img, x, y, 0xff00ffff);
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