/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:58:50 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/08 14:27:01 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"

// optimization potential for first dot and calculation in the first if
int	is_hit_plane(t_ray *ray, t_plane *plane)
{
	if (vec3_dot(ray->vec3, plane->normal) == 0)
	{
		// do inside of plane stuff
	}
	else
	{
		return (1);
	}
	return (0);
}

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

/// @brief positive dot means angle < 90, negative dot means angle > 90. zero
/// dot means angle == 90
/// @param ray 
/// @param plane 
/// @return 
int	should_invert_plane_normal(t_ray *ray, t_plane *plane)
{
	if (vec3_dot(ray->vec3, plane->normal) < 0.0f)
		return (0);
	return (1);
}

void	get_hit_data_plane(t_ray *ray, t_plane *plane)
{
	ray->results.hit_normal = plane->normal;
	if (should_invert_plane_normal(ray, plane) == 1)
		ray->results.hit_normal.v = -ray->results.hit_normal.v;
}
