/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 12:23:02 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/01 17:04:02 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "structs.h"
#include "consts.h"
#include "math.h" // for tan




// (1,1). 10x10

t_ray	*get_ray(int x, int y, t_camera *camera)
{
	t_vec3	point_on_img_plane;
	t_ray	*ray;

	ray = ft_calloc(1, sizeof(t_ray));
	point_on_img_plane.x = (2 * (((float)x + 0.5) / (float)WIDTH) - 1)\
* camera->window_info.aspect_ratio * camera->fov_scale;
	point_on_img_plane.y = (1 - 2 * (((float)y + 0.5)\
/ (float)HEIGHT)) * camera->fov_scale;
	point_on_img_plane.z = -1;
	ray->vec3.x = point_on_img_plane.x - camera->coords.x;
	ray->vec3.y = point_on_img_plane.y - camera->coords.y;
	ray->vec3.z = point_on_img_plane.z - camera->coords.z;
	ray->vec3 = normalize_vec3(ray->vec3);
	ray->orig = camera->coords;
	return (ray);
}
