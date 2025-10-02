/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:22:38 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/02 10:27:16 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math.h"
#include "math_inc.h"
#include "structs.h"

/// @brief calculates the determinent for the quadratic
/// @brief funtions for a vector and sphere
/// @brief example -> https://www.desmos.com/3d/opwztyzyal
/// @param ray
/// @param sphere
/// @return <  0 no intersection
/// @return == 0 one intersection
/// @return >  0 two intersections
float	sphere_intersects(t_ray ray, t_sphere sphere)
{
	float	disc;
	t_vec3	orig_center;
	float	f_tmp1;
	float	f_tmp2;

	orig_center = (t_vec3)(ray.orig.v - sphere.coords.v);
	f_tmp1 = vec3_length(orig_center);
	f_tmp2 = vec3_dot(ray.vec3, orig_center);
	disc = (f_tmp2 * f_tmp2) - \
((f_tmp1 * f_tmp1) - (sphere.radius * sphere.radius));
	return (disc);
}
