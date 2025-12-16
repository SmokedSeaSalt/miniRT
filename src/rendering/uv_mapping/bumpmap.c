/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bumpmap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 14:48:40 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/16 10:53:18 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "math_inc.h"
#include "rendering.h"
#include <math.h>

t_vec3	change_u_bump_normal(t_vec3 normal, int x_delta)
{
	t_vec3	u_vec;
	t_vec3	v_vec;

	set_u_and_v_vectors(&u_vec, &v_vec, normal);
	u_vec.v = u_vec.v + ((float)x_delta * 0.05f * normal.v);
	u_vec = vec3_normalize(u_vec);
	return (vec3_normalize(vec3_cross(v_vec, u_vec)));
}

t_vec3	change_v_bump_normal(t_vec3 normal, int y_delta)
{
	t_vec3	u_vec;
	t_vec3	v_vec;

	set_u_and_v_vectors(&u_vec, &v_vec, normal);
	v_vec.v = v_vec.v + ((float)y_delta * 0.05f * normal.v);
	v_vec = vec3_normalize(v_vec);
	return (vec3_normalize(vec3_cross(v_vec, u_vec)));
}


int	get_x_offset_value(t_ray *ray, t_uv_map *bumpmap)
{
	t_uv	offset_uv;
	int		pixels_index;

	offset_uv = ray->results.uv_coords;
	offset_uv.u += (1.0f / (float)bumpmap->png->width);
	offset_uv.u = fmodf(offset_uv.u, 1.0f);

	offset_uv.v = 1 - offset_uv.v;

	pixels_index = get_pixels_index(offset_uv, bumpmap->png);
	return (bumpmap->png->pixels[pixels_index]);
}

int	get_y_offset_value(t_ray *ray, t_uv_map *bumpmap)
{
	t_uv	offset_uv;
	int		pixels_index;

	offset_uv = ray->results.uv_coords;
	offset_uv.v += (1.0f / (float)bumpmap->png->height);
	offset_uv.v = fmodf(offset_uv.v, 1.0f);

	offset_uv.v = 1 - offset_uv.v;

	pixels_index = get_pixels_index(offset_uv, bumpmap->png);
	return (bumpmap->png->pixels[pixels_index]);
}

void	get_new_bump_normal(t_ray *ray, t_uv_map *bumpmap)
{
	t_uv uv;
	int	pixels_index;
	int	default_value;
	int	x_offset_delta;
	int	y_offset_delta;

	uv = ray->results.uv_coords;
	uv.v = 1 - uv.v;
	// get the value from the uv map
	//get midpoint pixel location
	pixels_index = get_pixels_index(uv, bumpmap->png);

	//get midpoint value
	default_value = bumpmap->png->pixels[pixels_index];

	//get midpoint x+     midpoint + (1 / uv_map->width)
	x_offset_delta = get_x_offset_value(ray, bumpmap) - default_value;
	//get midpoint y+
	y_offset_delta = get_y_offset_value(ray, bumpmap) - default_value;

	//do smart stuff
	ray->results.hit_normal = change_u_bump_normal(ray->results.hit_normal, x_offset_delta);
	ray->results.hit_normal = change_v_bump_normal(ray->results.hit_normal, y_offset_delta);

}

void	check_and_calcute_bumpmap(t_ray *ray, t_uv_map *bumpmap)
{
	// check if bumpmap is present
	if (bumpmap == NULL)
		return ;

	//calculate normal offset
	//set new normal
	get_new_bump_normal(ray, bumpmap);
}