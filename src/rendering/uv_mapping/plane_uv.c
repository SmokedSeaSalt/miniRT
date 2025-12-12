/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_uv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:54:37 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/12 16:22:48 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "consts.h"
#include "math_inc.h"
#include <math.h>
#include "consts.h"

static void	set_u_and_v_vectors(t_vec3 *u_vec, t_vec3 *v_vec, t_plane *plane)
{
	const t_vec3 world_up = vec3_new(0, 0, 1);// todo edge case for certain plane orientation?
	*u_vec = vec3_cross(plane->normal, world_up);
	*u_vec = vec3_normalize(*u_vec);
	*v_vec = vec3_cross(plane->normal, *u_vec);
	*v_vec = vec3_normalize(*v_vec);
}

static float	normalize_v(t_vec3 v_vec, t_vec3 center_to_hit_vec)
{
	float	v;
	float	normalized_v;

	v = vec3_dot(v_vec, center_to_hit_vec);
	if (v > 0)
		normalized_v = (fmod(v, PLANE_UV_HEIGHT) / PLANE_UV_HEIGHT) / PLANE_UV_HEIGHT;
	else
	{
		while (v < 0)
			v += PLANE_UV_HEIGHT;
		normalized_v = v / PLANE_UV_HEIGHT;
	}
	return (normalized_v);
}

static float	normalize_u(t_vec3 u_vec, t_vec3 center_to_hit_vec)
{
	float	u;
	float		normalized_u;
	
	u = vec3_dot(u_vec, center_to_hit_vec);
	if (u > 0)
		normalized_u = (fmod(u, PLANE_UV_WIDTH) / PLANE_UV_WIDTH) / PLANE_UV_WIDTH;
	else
	{
		while (u < 0)
			u += PLANE_UV_WIDTH;
		normalized_u = u / PLANE_UV_WIDTH;
	}
	return (normalized_u);
}

t_uv	get_plane_uv(t_ray *ray, t_plane *plane)
{
	t_uv	uv;
	t_vec3	u_vec;
	t_vec3	v_vec;
	t_vec3	hit_point;
	t_vec3	center_to_hit_vec;

	set_u_and_v_vectors(&u_vec, &v_vec, plane);
	hit_point.v = ray->orig.v + (ray->vec3.v * ray->results.hit_dist);
	center_to_hit_vec.v = hit_point.v - plane->coords.v;

	uv.u = normalize_u(u_vec, center_to_hit_vec);
	uv.v = normalize_v(v_vec, center_to_hit_vec);

	

	// uv.u = fmod(vec3_dot(u_vec, center_to_hit_vec), PLANE_UV_WIDTH) / PLANE_UV_WIDTH;
	// uv.v = fmod(vec3_dot(v_vec, center_to_hit_vec), PLANE_UV_HEIGHT) / PLANE_UV_HEIGHT;
	uv.v = 1 - uv.v;
	return (uv);
}
