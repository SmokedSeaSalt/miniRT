/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:22:38 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/01 16:57:48 by mvan-rij         ###   ########.fr       */
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
	//todo:
	// write unit test
	// add radius calculation to struct and parsing

	disc = powf(vec3_dot(ray.vec3, (t_vec3)(ray.orig.v - sphere.coords.v)), 2.0) \
- (powf(vec3_length((t_vec3)(ray.orig.v - sphere.coords.v)), 2.0) \
- powf((sphere.diameter * 0.5), 2.0));
	return (disc);
}
