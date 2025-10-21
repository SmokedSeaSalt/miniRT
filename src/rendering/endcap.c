/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endcap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:11:44 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/21 16:42:05 by mvan-rij         ###   ########.fr       */
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
	ray->results.hit_normal = endcap->normal;
	if (is_vec3_angle_acute(&ray->vec3, &endcap->normal) == 1)
		ray->results.hit_normal.v = -ray->results.hit_normal.v;
	ray->results.obj_color = endcap->color;
	set_light_hit_angle_and_intensity(scene, ray);
}