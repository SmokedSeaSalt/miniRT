/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_uv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:33:13 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/12 13:31:20 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "consts.h"
#include "math_inc.h"
#include <math.h>

t_uv get_sphere_uv(t_ray *ray, t_sphere *sphere)
{
	t_vec3	d;
	t_uv	uv;
	t_vec3	hit_point;

	hit_point.v = ray->orig.v + (ray->vec3.v * ray->results.hit_dist);
	d.v = hit_point.v - sphere->coords.v;
	d = vec3_normalize(d);
	uv.u = 0.5 + (atan2(d.x, d.y) / (2 * PI));
	uv.v = 0.5 + (asin(d.z) / PI);
	uv.u = fmax(0, fmin(1, uv.u));
	uv.v = fmax(0, fmin(1, uv.v));
	return (uv);
}