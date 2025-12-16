/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_uv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:54:37 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/16 14:15:03 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "consts.h"
#include "math_inc.h"
#include "consts.h"
#include "rendering.h"
#include <math.h>

static float	get_normalized_v(t_vec3 v_vec, t_vec3 center_to_hit_vec)
{
	float	v;

	v = vec3_dot(v_vec, center_to_hit_vec);
	v = fmod(v, PLANE_UV_HEIGHT);
	if (v < 0)
		v += PLANE_UV_HEIGHT;
	return (v / PLANE_UV_HEIGHT);
}

static float	get_normalized_u(t_vec3 u_vec, t_vec3 center_to_hit_vec)
{
	float	u;

	u = vec3_dot(u_vec, center_to_hit_vec);
	u = fmod(u, PLANE_UV_WIDTH);
	if (u < 0)
		u += PLANE_UV_WIDTH;
	return (u / PLANE_UV_WIDTH);
}

t_uv	get_plane_uv(t_ray *ray, t_plane *plane)
{
	t_uv	uv;
	t_vec3	u_vec;
	t_vec3	v_vec;
	t_vec3	hit_point;
	t_vec3	center_to_hit_vec;

	set_u_and_v_vectors(&u_vec, &v_vec, ray->results.hit_normal);
	hit_point.v = ray->orig.v + (ray->vec3.v * ray->results.hit_dist);
	center_to_hit_vec.v = hit_point.v - plane->coords.v;
	uv.u = get_normalized_u(u_vec, center_to_hit_vec);
	uv.v = get_normalized_v(v_vec, center_to_hit_vec);
	uv.v = 1 - uv.v;
	uv.u = 1 - uv.u;
	return (uv);
}
