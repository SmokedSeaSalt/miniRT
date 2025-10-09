/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 13:42:02 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/09 10:05:49 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"

void	get_hit_data_sphere(t_ray *ray, t_sphere *sphere)
{
	ray->results.hit_normal = sphere_normal_at(ray, sphere);
	ray->results.obj_color = sphere->color;
}
