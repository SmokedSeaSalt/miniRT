/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:42:02 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/12 12:14:38 by mvan-rij         ###   ########.fr       */
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
	t_uv uv;
	ray->results.hit_normal = sphere_normal_at(ray, sphere);
	if (sphere->uv_color != NULL)
	{
		uv = get_sphere_uv(ray, sphere);
		ray->results.obj_color = uv_checkerboard(uv, sphere->color);
	}
	else
		ray->results.obj_color = sphere->color;
	set_light_hit_angle_and_intensity(scene, ray);
}
