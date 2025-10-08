/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_sphere.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:22:38 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/08 13:28:25 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "math_inc.h"
#include "structs.h"

/// @brief calculates the determinent for the quadratic
/// @brief funtions for a vector and sphere
/// @brief example -> https://www.desmos.com/3d/vb1nicgnja
/// @param ray
/// @param sphere
/// @return <  0 no intersection
/// @return == 0 one intersection
/// @return >  0 two intersections
float	sphere_intersects(t_ray *ray, t_sphere *sphere)
{
	float	disc;
	t_vec3	orig_center;
	float	f_tmp1;
	float	f_tmp2;

	orig_center = (t_vec3)(ray->orig.v - sphere->coords.v);
	f_tmp1 = vec3_length(orig_center);
	f_tmp2 = vec3_dot(ray->vec3, orig_center);
	disc = (f_tmp2 * f_tmp2) - \
((f_tmp1 * f_tmp1) - (sphere->radius * sphere->radius));
	return (disc);
}

float	get_hit_dist_sphere(t_ray *ray, t_sphere *sphere)
{
	float	disc;
	float	distance1;
	float	distance2;
	float	f_tmp2;

	disc = sphere_intersects(ray, sphere);
	if (disc < 0.0f)
		return (disc);
	f_tmp2 = vec3_dot(ray->vec3, (t_vec3)(ray->orig.v - sphere->coords.v));
	distance1 = -f_tmp2 + sqrt(disc);
	distance2 = -f_tmp2 - sqrt(disc);
	return (decide_closest_distance(distance1, distance2));
}

t_vec3	sphere_normal_at(t_ray *ray, t_sphere *sphere)
{
	t_vec3	hit_point;
	t_vec3	normal;
	float	length_ray_to_cent;

	hit_point.v = ray->orig.v + (ray->vec3.v * ray->results.hit_dist);
	normal.v = hit_point.v - sphere->coords.v;
	length_ray_to_cent = vec3_length((t_vec3)(ray->orig.v - sphere->coords.v));
	if (length_ray_to_cent < sphere->radius)
		normal.v = -normal.v;
	normal = vec3_normalize(normal);
	return (normal);
}

int	is_hit_sphere(t_ray *ray, t_sphere *sphere)
{
	if (sphere_intersects(ray, sphere) < 0.0f)
		return (0);
	else
		return (1);
}