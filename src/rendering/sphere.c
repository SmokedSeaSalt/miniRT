/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:42:02 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/12 11:50:31 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"
#include "rendering.h"

/// @brief fills ray.results with the relevant sphere data.
/// @param ray
/// @param sphere
/// @param scene
void	get_hit_data_sphere(t_ray *ray, t_sphere *sphere, t_scene *scene)
{
	t_uv			uv;
	const t_uv_map	*uv_map = ray->results.object->uv_color;

	
	ray->results.hit_normal = sphere_normal_at(ray, sphere);
	if (uv_map != NULL)
	{
		uv = get_sphere_uv(ray, sphere);
		if (uv_map->type == CHECKERBOARD)
			ray->results.obj_color = uv_checkerboard(uv, sphere->color);
		else if (uv_map->type == PNG)
			ray->results.obj_color = get_uv_value_png(uv, uv_map->png);
			
	}
	else
		ray->results.obj_color = sphere->color;
	set_light_hit_angle_and_intensity(scene, ray);
}
