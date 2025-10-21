/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:41:05 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/21 16:48:25 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"
#include "rendering.h"

/// @brief fills ray.results with the relevant plane data.
/// @param ray
/// @param plane
/// @param scene
void	get_hit_data_plane(t_ray *ray, t_plane *plane, t_scene *scene)
{
	ray->results.hit_normal = plane->normal;
	if (is_vec3_angle_acute(&ray->vec3, &plane->normal) == 1)
		ray->results.hit_normal.v = -ray->results.hit_normal.v;
	ray->results.obj_color = plane->color;
	set_light_hit_angle_and_intensity(scene, ray);
}