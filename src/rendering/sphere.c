/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:42:02 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/23 14:04:02 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"
#include "rendering.h"

/// @brief fills ray.results with the relevant sphere data.
/// @param ray
/// @param sphere
/// @param scene
void	get_hit_data_sphere(t_ray *ray, t_sphere *sphere, t_scene *scene)
{
	ray->results.uv_color = sphere->uv_color;
	ray->results.bump = sphere->bump;
	ray->results.hit_normal = sphere_normal_at(ray, sphere);
	ray->results.uv_coords = get_sphere_uv(ray, sphere);
	if (sphere->uv_color.type == DEFAULT)
		ray->results.obj_color = sphere->color;
	else if (sphere->uv_color.type == CHECKERBOARD)
		ray->results.obj_color = uv_checkerboard(ray->results.uv_coords, \
sphere->color);
	else if (sphere->uv_color.type == PNG)
		ray->results.obj_color = get_uv_value_png(ray->results.uv_coords, \
sphere->uv_color.png);
	check_and_calcute_bumpmap(ray, ray->results.bump);
	set_light_hit_angle_and_intensity(scene, ray);
}
