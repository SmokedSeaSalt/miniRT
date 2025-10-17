/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endcap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 14:11:44 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/17 11:20:15 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"
#include "rendering.h"

// optimization potential for first dot and calculation in the first if
int	is_hit_endcap(t_ray *ray, t_endcap *endcap)
{
	if (vec3_dot(ray->vec3, endcap->normal) == 0)
		return (0);
	return (1);

}

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

void	get_hit_data_endcap(t_ray *ray, t_endcap *endcap, t_scene *scene)
{
	ray->results.hit_normal = endcap->normal;
	if (is_vec3_angle_acute(&ray->vec3, &endcap->normal) == 1)
		ray->results.hit_normal.v = -ray->results.hit_normal.v;
	ray->results.obj_color = endcap->color;
	set_light_hit_angle_and_intensity(scene, ray);
}