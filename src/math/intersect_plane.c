/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_plane.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 14:58:50 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/08 16:47:22 by egrisel          ###   ########.fr       */
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







