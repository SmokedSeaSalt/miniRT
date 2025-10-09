/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:41:05 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/09 12:41:05 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"

void	get_hit_data_plane(t_ray *ray, t_plane *plane, t_scene *scene)
{
	(void)scene;
	ray->results.hit_normal = plane->normal;
	if (is_vec3_angle_acute(&ray->orig, &plane->normal) == 1)
		ray->results.hit_normal.v = -ray->results.hit_normal.v;
	// ray->results.light_intensity = get_light_hit_angle(t_ray *ray,)
	//get light intensity
}