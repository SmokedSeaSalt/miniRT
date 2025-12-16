/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:41:05 by egrisel           #+#    #+#             */
/*   Updated: 2025/12/16 14:30:36 by mvan-rij         ###   ########.fr       */
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
	ray->results.uv_color = plane->uv_color;
	ray->results.bump = plane->bump;
	ray->results.hit_normal = plane->normal;
	ray->results.uv_coords = get_plane_uv(ray, plane);
	if (is_vec3_angle_acute(&ray->vec3, &plane->normal) == 1)
		ray->results.hit_normal.v = -ray->results.hit_normal.v;
	if (plane->uv_color != NULL)
	{
		if (plane->uv_color->type == CHECKERBOARD)
			ray->results.obj_color = uv_checkerboard(ray->results.uv_coords, \
plane->color);
		else if (plane->uv_color->type == PNG)
			ray->results.obj_color = get_uv_value_png(ray->results.uv_coords, \
plane->uv_color->png);
	}
	else
		ray->results.obj_color = plane->color;
	check_and_calcute_bumpmap(ray, ray->results.bump);
	set_light_hit_angle_and_intensity(scene, ray);
}
