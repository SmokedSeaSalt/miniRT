/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:18:10 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/15 16:16:53 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"
#include "rendering.h"
#include <math.h>
#include <stdio.h>															//remove later

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
	//printf("disc = %f\n", disc);
	return (disc);
}

int	is_hit_cylinder(t_ray *ray, t_cylinder *cylinder)
{
	if (cylinder_intersects(ray, cylinder) < 0.0f)
		return (0);
	else if (get_hit_dist_cylinder(ray, cylinder) < 0.0f)
		return (0);
	return (1);
}

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


int is_hit_within_height(t_ray *ray, t_cylinder *cylinder, float hit_dist)
{
	float hit_height;

	hit_height = get_hit_height(ray, cylinder, hit_dist);
	if (hit_height < (0.5 * cylinder->height) && \
hit_height > (-0.5 * cylinder->height))
		return (1);
	return (0);
}

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

	//printf("rc_cross x = %f , y = %f , z = %f\n", rc_cross.x, rc_cross.y, rc_cross.z);
	//printf("orig_dist x = %f , y = %f , z = %f\n", orig_dist.x, orig_dist.y, orig_dist.z);

	tmp1 = vec3_dot(rc_cross, vec3_cross(orig_dist, cylinder->orientation));

	//printf("tmp1 = %f \n", tmp1);

	distances[0] = (tmp1 + sqrt(disc)) / vec3_dot(rc_cross, rc_cross);
	distances[1] = (tmp1 - sqrt(disc)) / vec3_dot(rc_cross, rc_cross);
	if (is_hit_within_height(ray, cylinder, distances[0]) == 0)
		distances[0] = -1;
	if (is_hit_within_height(ray, cylinder, distances[1]) == 0)
		distances[1] = -1;
	//printf("hitdist1 = %f , hitdist2 = %f\n", distances[0], distances[1]);
	return (decide_closest_distance(distances[0], distances[1]));
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

	//todo flip normal if inside cylinder
	orig_dist.v = cylinder->coords.v - ray->orig.v;
	hit_height = get_hit_height(ray, cylinder, ray->results.hit_dist);
	tmp1.v = (ray->vec3.v * ray->results.hit_dist);
	tmp2.v = (cylinder->orientation.v * hit_height);
	normal.v = tmp1.v - tmp2.v - orig_dist.v;
	normal = vec3_normalize(normal);
	return (normal);
}

void	get_hit_data_cylinder(t_ray *ray, t_cylinder *cylinder, t_scene *scene)
{
	ray->results.hit_normal = cylinder_normal_at(ray, cylinder);
	ray->results.obj_color = cylinder->color;
	set_light_hit_angle_and_intensity(scene, ray);
}
