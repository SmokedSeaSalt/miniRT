/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:18:10 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/23 14:03:26 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"
#include "rendering.h"
#include <math.h>

/// @brief calculates the discriminant for the quadratic
/// @brief funtions for a vector and cylinder
/// @brief example -> https://www.desmos.com/3d/7vd5a6lml0
/// @param ray
/// @param cylinder
/// @return <  0 no intersection
/// @return == 0 one intersection
/// @return >  0 two intersections
float	cylinder_intersects(t_ray *ray, t_cylinder *cylinder)
{
	float	disc;
	t_vec3	orig_dist;
	t_vec3	rc_cross;
	float	tmp1;
	float	tmp2;

	rc_cross = vec3_cross(ray->vec3, cylinder->orientation);
	orig_dist.v = cylinder->coords.v - ray->orig.v;
	tmp1 = vec3_dot(rc_cross, rc_cross) * cylinder->radius * cylinder->radius;
	tmp2 = vec3_dot(orig_dist, rc_cross);
	disc = tmp1 - (tmp2 * tmp2);
	return (disc);
}

/// @brief calculates the distance from ray origin to cylinder surface.
/// @param ray
/// @param cylinder
/// @return closest distance as a float.
float	get_hit_dist_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	float	disc;
	t_vec3	rc_cross;
	t_vec3	orig_dist;
	float	distances[2];
	float	tmp1;

	disc = cylinder_intersects(ray, cylinder);
	rc_cross = vec3_cross(ray->vec3, cylinder->orientation);
	orig_dist.v = cylinder->coords.v - ray->orig.v;
	tmp1 = vec3_dot(rc_cross, vec3_cross(orig_dist, cylinder->orientation));
	distances[0] = (tmp1 + sqrt(disc)) / vec3_dot(rc_cross, rc_cross);
	distances[1] = (tmp1 - sqrt(disc)) / vec3_dot(rc_cross, rc_cross);
	if (is_hit_within_height(ray, cylinder, distances[0]) == 0)
		distances[0] = -1;
	if (is_hit_within_height(ray, cylinder, distances[1]) == 0)
		distances[1] = -1;
	return (decide_closest_distance(distances[0], distances[1]));
}

/// @brief checks if the ray was cast from within the sphere to check if
/// @brief the surface normal needs to be inverted.
/// @param ray
/// @param cylinder
/// @return 1 if ray started from within, 0 if ray started outside.
int	ray_origin_within_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	t_vec3	vec_oc;
	float	proj;
	t_vec3	closest_point;
	float	dist2;
	float	radius2;

	vec_oc.v = ray->orig.v - cylinder->coords.v;
	proj = vec3_dot(vec_oc, cylinder->orientation);
	if (proj > (0.5 * cylinder->height) || proj < (-0.5 * cylinder->height))
		return (0);
	closest_point.v = cylinder->coords.v + cylinder->orientation.v * proj;
	dist2 = vec3_length((t_vec3)(ray->orig.v - closest_point.v));
	dist2 = dist2 * dist2;
	radius2 = cylinder->radius * cylinder->radius;
	if (dist2 <= radius2)
		return (1);
	return (0);
}

/// @brief Calculate the normal vector of the hit on the cylinder.
/// Needs ray.results.hit_dist to be known
/// @param ray
/// @param cylinder
/// @return t_vec3 with normal vector
t_vec3	cylinder_normal_at(t_ray *ray, t_cylinder *cylinder)
{
	float	hit_height;
	t_vec3	orig_dist;
	t_vec3	normal;
	t_vec3	tmp1;
	t_vec3	tmp2;

	orig_dist.v = cylinder->coords.v - ray->orig.v;
	hit_height = get_hit_height(ray, cylinder, ray->results.hit_dist);
	tmp1.v = (ray->vec3.v * ray->results.hit_dist);
	tmp2.v = (cylinder->orientation.v * hit_height);
	normal.v = tmp1.v - tmp2.v - orig_dist.v;
	normal = vec3_normalize(normal);
	if (ray_origin_within_cylinder(ray, cylinder) == 1)
		normal.v = -normal.v;
	return (normal);
}

/// @brief fills ray.results with the relevant cylinder data.
/// @param ray
/// @param cylinder
/// @param scene
void	get_hit_data_cylinder(t_ray *ray, t_cylinder *cylinder, t_scene *scene)
{
	ray->results.uv_color = cylinder->uv_color;
	ray->results.bump = cylinder->bump;
	ray->results.hit_normal = cylinder_normal_at(ray, cylinder);
	ray->results.uv_coords = get_cylinder_uv(ray, cylinder);
	if (cylinder->uv_color.type == DEFAULT)
		ray->results.obj_color = cylinder->color;
	else if (cylinder->uv_color.type == CHECKERBOARD)
		ray->results.obj_color = uv_checkerboard(ray->results.uv_coords, \
cylinder->color);
	else if (cylinder->uv_color.type == PNG)
		ray->results.obj_color = get_uv_value_png(ray->results.uv_coords, \
cylinder->uv_color.png);
	check_and_calcute_bumpmap(ray, ray->results.bump);
	set_light_hit_angle_and_intensity(scene, ray);
}
