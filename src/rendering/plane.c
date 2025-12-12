/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:41:05 by egrisel           #+#    #+#             */
/*   Updated: 2025/12/12 15:50:04 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"
#include "rendering.h"

/// @brief fills ray.results with the relevant plane data.
/// @param ray
/// @param plane
/// @param scene
void	get_hit_data_plane(t_ray *ray, t_plane *plane, t_scene *scene)
{
	t_uv	uv;

	ray->results.hit_normal = plane->normal;
	if (is_vec3_angle_acute(&ray->vec3, &plane->normal) == 1)
		ray->results.hit_normal.v = -ray->results.hit_normal.v;
		
	if (plane->uv_color != NULL)
	{
		uv = get_plane_uv(ray, plane);
		if (plane->uv_color->type == CHECKERBOARD)
			ray->results.obj_color = uv_checkerboard(uv, plane->color);
		else if (plane->uv_color->type == PNG)
			ray->results.obj_color = get_uv_value_png(uv, plane->uv_color->png);
	}
	else
		ray->results.obj_color = plane->color;
	set_light_hit_angle_and_intensity(scene, ray);
}
