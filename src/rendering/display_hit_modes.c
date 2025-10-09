/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_hit_modes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:30:44 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/09 09:43:55 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "structs.h"
#include "MLX42.h"

void	display_normal(t_ray *ray, int x, int y, t_scene *scene)
{
	int	r;
	int	g;
	int	b;
	int	colour;

	g = (int)(0.5f * (ray->results.hit_normal.y + 1) * 0xff);
	b = (int)(0.5f * (ray->results.hit_normal.z + 1) * 0xff);
	r = (int)(0.5f * (ray->results.hit_normal.x + 1) * 0xff);
	colour = (r << 3 * 8) + (g << 2 * 8) + (b << 1 * 8) + 0xff;
	mlx_put_pixel(scene->g_img, x, y, colour);
}

void	display_xyz(t_ray *ray, int x, int y, t_scene *scene)
{
	int	r;
	int	g;
	int	b;
	int	colour;

	r = (int)(fabs(ray->results.hit_normal.x) * 0xff);
	g = (int)(fabs(ray->results.hit_normal.y) * 0xff);
	b = (int)(fabs(ray->results.hit_normal.z) * 0xff);
	colour = (r << 3 * 8) + (g << 2 * 8) + (b << 1 * 8) + 0xff;
	mlx_put_pixel(scene->g_img, x, y, colour);
}

void	display_default(t_ray *ray, int x, int y, t_scene *scene)
{
	int	r;
	int	colour;

	r = (int)(ray->results.light_intensity * 0xff);
	colour = (r << 3 * 8) + (r << 2 * 8) + (r << 1 * 8) + 0xff;
	mlx_put_pixel(scene->g_img, x, y, colour);

}