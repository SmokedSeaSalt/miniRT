/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 16:27:34 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/08 17:07:40 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"

float	angle_between_ray_and_light(t_ray *ray, t_light *light)
{
	return (get_angle_between_vec3(&ray->orig, &light->coords));
}

void	get_light_hit_angle(t_ray *ray) // todo add scene as param
{
	t_vec3	hit_point;
	//light coords
	//all objects to check if hit any
	
	hit_point.v = ray->orig.v + (ray->vec3.v * ray->results.hit_dist);
}