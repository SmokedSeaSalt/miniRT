/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:41:05 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/08 17:09:21 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"

void	get_hit_data_plane(t_ray *ray, t_plane *plane)
{
	ray->results.hit_normal = plane->normal;
	if (is_vec3_angle_acute(&ray->orig, &plane->normal) == 1)
		ray->results.hit_normal.v = -ray->results.hit_normal.v;
	// ray->results.light_intensity = get_light_hit_angle(t_ray *ray,)
	//get light intensity
}