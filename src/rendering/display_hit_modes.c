/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_hit_modes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:30:44 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/07 10:55:09 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "structs.h"
#include "MLX42.h"

void display_normal(t_ray *ray, int x, int y, t_scene *scene)
{
	int r;
	int g;
	int b;
	int colour;

	g = (int)(0.5f * (ray->results.normal_at.y + 1) * 0xff);
	b = (int)(0.5f * (ray->results.normal_at.z + 1) * 0xff);
	r = (int)(0.5f * (ray->results.normal_at.x + 1) * 0xff);
	colour = (r << 3*8) + (g << 2*8) + (b << 1*8) + 0xff;
	mlx_put_pixel(scene->g_img, x, y, colour);
}

void display_xyz(t_ray *ray, int x, int y, t_scene *scene)
{
	int r;
	int g;
	int b;
	int colour;

	r = (int)(fabs(ray->results.normal_at.x) * 0xff);
	g = (int)(fabs(ray->results.normal_at.y) * 0xff);
	b = (int)(fabs(ray->results.normal_at.z) * 0xff);
	colour = (r << 3*8) + (g << 2*8) + (b << 1*8) + 0xff;
	mlx_put_pixel(scene->g_img, x, y, colour);
}
