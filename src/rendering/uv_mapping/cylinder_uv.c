/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_uv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:46:26 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/12 16:56:18 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rendering.h"
#include "consts.h"
#include "math_inc.h"
#include <math.h>

t_uv get_endcapbot_uv(t_ray *ray, t_endcap *endcap);
t_uv get_endcaptop_uv(t_ray *ray, t_endcap *endcap);

t_uv get_cylinder_uv(t_ray *ray, t_cylinder *cylinder)
{
	t_vec3		d;
	t_uv		uv;
	t_vec3		hit_point;
	const float	hit_height = get_hit_height(ray, cylinder, ray->results.hit_dist) + ( 0.5 * cylinder->height);

	hit_point.v = ray->orig.v + (ray->vec3.v * ray->results.hit_dist);
	d.v = hit_point.v - cylinder->coords.v;
	uv.u = 0.5 + (atan2(d.x, d.y) / (2 * PI));
	uv.u = fmax(0, fmin(1, uv.u));
	uv.v = (hit_height / cylinder->height) * 0.7;
	return (uv);
}

static void	set_u_and_v_vectors(t_vec3 *u_vec, t_vec3 *v_vec, t_vec3 normal)
{
	const t_vec3 world_up = vec3_new(0, 0, 1);// todo edge case for certain plane orientation?
	*u_vec = vec3_cross(normal, world_up);
	*u_vec = vec3_normalize(*u_vec);
	*v_vec = vec3_cross(normal, *u_vec);
	*v_vec = vec3_normalize(*v_vec);
}

t_uv get_endcap_uv(t_ray *ray, t_endcap *endcap)
{
	if (ray->results.object->type == ENDCAPBOT)
		return (get_endcapbot_uv(ray, endcap));
	else
		return (get_endcaptop_uv(ray, endcap));
}

t_uv get_endcapbot_uv(t_ray *ray, t_endcap *endcap)
{
	t_uv	uv;
	t_vec3	u_vec;
	t_vec3	v_vec;
	t_vec3	center_to_hit_vec;
	t_vec3	hit_point;

	set_u_and_v_vectors(&u_vec, &v_vec, endcap->normal);
	hit_point.v = ray->orig.v + (ray->vec3.v * ray->results.hit_dist);
	center_to_hit_vec.v = hit_point.v - endcap->coords.v;

	uv.u = (vec3_dot(u_vec, center_to_hit_vec) / endcap->radius) * 0.3;
	uv.v = (vec3_dot(v_vec, center_to_hit_vec) / endcap->radius) * 0.3;
	uv.u += 0.85;
	uv.v += 0.15;
	return (uv);
}

t_uv get_endcaptop_uv(t_ray *ray, t_endcap *endcap)
{
	t_uv	uv;
	t_vec3	u_vec;
	t_vec3	v_vec;
	t_vec3	center_to_hit_vec;
	t_vec3	hit_point;

	set_u_and_v_vectors(&u_vec, &v_vec, endcap->normal);
	hit_point.v = ray->orig.v + (ray->vec3.v * ray->results.hit_dist);
	center_to_hit_vec.v = hit_point.v - endcap->coords.v;

	uv.u = (vec3_dot(u_vec, center_to_hit_vec) / endcap->radius) * 0.3;
	uv.v = (vec3_dot(v_vec, center_to_hit_vec) / endcap->radius) * 0.3;
	uv.u += 0.85;
	uv.v += 0.85;
	return (uv);
}