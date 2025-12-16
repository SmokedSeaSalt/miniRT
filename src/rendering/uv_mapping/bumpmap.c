/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:48:40 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/16 14:28:11 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"
#include "rendering.h"
#include <math.h>

t_vec3	convert_color_to_vec(t_color rgb)
{
	t_vec3	vec;

	vec = vec3_new((rgb.r / 255.0f) * 2.0f - 1.0f,
			(rgb.g / 255.0f) * 2.0f - 1.0f,
			((rgb.b / 255.0f)));
	vec = vec3_normalize(vec);
	return (vec);
}

/// @brief add the bumpmap normal offset to the ray hit normal.
/// @param hit hit surface normal.
/// @param normal normal offset according to bumpmap.
/// @return new hit normal.
t_vec3	add_normal_offset(t_vec3 hit, t_vec3 normal)
{
	t_vec3	tangent;
	t_vec3	bitangent;
	t_vec3	ret;

	set_u_and_v_vectors(&tangent, &bitangent, hit);
	ret.x = tangent.x * normal.x + bitangent.x * normal.y + hit.x * normal.z;
	ret.y = tangent.y * normal.x + bitangent.y * normal.y + hit.y * normal.z;
	ret.z = tangent.z * normal.x + bitangent.z * normal.y + hit.z * normal.z;
	ret = vec3_normalize(ret);
	return (ret);
}

void	get_new_bump_normal(t_ray *ray, t_uv_map *bumpmap)
{
	t_color	normal_map_rgb;
	t_vec3	normal_vec_offset;

	normal_map_rgb = get_uv_value_png(ray->results.uv_coords, bumpmap->png);
	normal_vec_offset = convert_color_to_vec(normal_map_rgb);
	ray->results.hit_normal = add_normal_offset(ray->results.hit_normal,
			normal_vec_offset);
}

void	check_and_calcute_bumpmap(t_ray *ray, t_uv_map *bumpmap)
{
	if (bumpmap == NULL)
		return ;
	get_new_bump_normal(ray, bumpmap);
}
