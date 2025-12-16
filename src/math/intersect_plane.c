/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:58:50 by egrisel           #+#    #+#             */
/*   Updated: 2025/12/16 14:07:45 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"

/// @brief check function for if the ray hits a plane or not.
/// @param ray
/// @param plane
/// @return 1 on hit, 0 on miss.
int	is_hit_plane(t_ray *ray, t_plane *plane)
{
	if (vec3_dot(ray->vec3, plane->normal) == 0)
		return (0);
	return (1);
}

/// @brief get the distance from ray origin to plane.
/// @param ray
/// @param plane
/// @return distance as float.
float	git_hit_dist_plane(t_ray *ray, t_plane *plane)
{
	float	d;
	float	numerator;
	float	denomenator;

	numerator = vec3_dot((t_vec3)(plane->coords.v - ray->orig.v),
			plane->normal);
	denomenator = vec3_dot(ray->vec3, plane->normal);
	d = numerator / denomenator;
	return (d);
}
