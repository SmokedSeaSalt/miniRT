/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 14:58:50 by mvan-rij          #+#    #+#             */
/*   Updated: 2026/01/02 14:07:45 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"
#include "rendering.h"

/// @brief check function for if the ray hits a cylinder or not.
/// @param ray
/// @param cylinder
/// @return	1 if hit, 0 if miss.
int	is_hit_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	if (cylinder_intersects(ray, cylinder) < 0.0f)
		return (0);
	else if (get_hit_dist_cylinder(ray, cylinder) < 0.0f)
		return (0);
	return (1);
}

/// @brief calculates the hit height based on the origin and
/// @brief direction of the cylinder base.
/// @param ray
/// @param cylinder
/// @param hit_dist
/// @return distance from origin height.
float	get_hit_height(t_ray *ray, t_cylinder *cylinder, float hit_dist)
{
	t_vec3	orig_dist;
	float	hit_height;
	t_vec3	tmp1;

	orig_dist.v = cylinder->coords.v - ray->orig.v;
	tmp1.v = (ray->vec3.v * hit_dist) - orig_dist.v;
	hit_height = vec3_dot(cylinder->orientation, tmp1);
	return (hit_height);
}

/// @brief a boundry check to check wether the hit height fits within
/// @brief the cylinder height.
/// @param ray
/// @param cylinder
/// @param hit_dist
/// @return 1 on height within cylinder limits. 0 outside cylinder limits.
int	is_hit_within_height(t_ray *ray, t_cylinder *cylinder, float hit_dist)
{
	float	hit_height;

	hit_height = get_hit_height(ray, cylinder, hit_dist);
	if (hit_height < (0.5 * cylinder->height) && \
hit_height > (-0.5 * cylinder->height))
		return (1);
	return (0);
}
