/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endcap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:11:44 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/23 14:03:03 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"
#include "rendering.h"

/// @brief check if the ray intersects with the endcap plane.
/// @param ray
/// @param endcap
/// @return 1 if ray hits plane, 0 if ray misses plane.
int	is_hit_endcap(t_ray *ray, t_endcap *endcap)
{
	if (vec3_dot(ray->vec3, endcap->normal) == 0)
		return (0);
	return (1);
}

/// @brief calculates the distance from ray origin to endcap surface.
/// @brief also checks if the hit is within the sphere surface.
/// @param ray
/// @param endcap
/// @return closest distance as a float.
/// @return is minus if hit is outside sphere range.
float	get_hit_dist_endcap(t_ray *ray, t_endcap *endcap)
{
	float	dist;
	float	numerator;
	float	denomenator;
	t_vec3	tmp1;

	numerator = vec3_dot((t_vec3)(endcap->coords.v - ray->orig.v),
			endcap->normal);
	denomenator = vec3_dot(ray->vec3, endcap->normal);
	dist = numerator / denomenator;
	tmp1.v = (ray->vec3.v * dist) - (endcap->coords.v - ray->orig.v);
	if (vec3_dot(tmp1, tmp1) > (endcap->radius * endcap->radius))
		return (-1.0f);
	return (dist);
}

/// @brief fills ray.results with the relevant endcap data.
/// @param ray
/// @param endcap
/// @param scene
void	get_hit_data_endcap(t_ray *ray, t_endcap *endcap, t_scene *scene)
{
	ray->results.uv_color = endcap->uv_color;
	ray->results.bump = endcap->bump;
	ray->results.hit_normal = endcap->normal;
	ray->results.uv_coords = get_endcap_uv(ray, endcap);
	if (is_vec3_angle_acute(&ray->vec3, &endcap->normal) == 1)
		ray->results.hit_normal.v = -ray->results.hit_normal.v;
	if (endcap->uv_color.type == DEFAULT)
		ray->results.obj_color = endcap->color;
	else if (endcap->uv_color.type == CHECKERBOARD)
		ray->results.obj_color = uv_checkerboard(ray->results.uv_coords, \
endcap->color);
	else if (endcap->uv_color.type == PNG)
		ray->results.obj_color = get_uv_value_png(ray->results.uv_coords, \
endcap->uv_color.png);
	check_and_calcute_bumpmap(ray, ray->results.bump);
	set_light_hit_angle_and_intensity(scene, ray);
}
