/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_hit_modes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:30:44 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/21 12:52:06 by mvan-rij         ###   ########.fr       */
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
	float	r;
	float	b;
	float	g;
	int		colour;


	r = (ray->results.light_intensity.r + scene->ambient->intensity.r);
	if (r > 1.0f)
		r = 1.0f;
	g = (ray->results.light_intensity.g + scene->ambient->intensity.g);
	if (g > 1.0f)
		g = 1.0f;
	b = (ray->results.light_intensity.b + scene->ambient->intensity.b);
	if (b > 1.0f)
		b = 1.0f;
	r = r * ray->results.obj_color.r;
	g = g * ray->results.obj_color.g;
	b = b * ray->results.obj_color.b;
	colour = ((int)r << 3 * 8) + ((int)g << 2 * 8) + ((int)b << 1 * 8) + 0xff;
	mlx_put_pixel(scene->g_img, x, y, colour);
}

void	display_light_intensity(t_ray *ray, int x, int y, t_scene *scene)
{
	int b;
	int	colour;
	float brightness;

	brightness = ((ray->results.light_intensity.x + \
ray->results.light_intensity.y + ray->results.light_intensity.z) * 0.3333f);
	brightness += scene->ambient->ratio;
	if (brightness > 1.0f)
		brightness = 1.0f;
	b = (int)(brightness * 0xff);
	colour = (b << 3 * 8) + (b << 2 * 8) + (b << 1 * 8) + 0xff;
	mlx_put_pixel(scene->g_img, x, y, colour);
}

void	display_distance(t_ray *ray, int x, int y, t_scene *scene)
{
	const float max_dist = 2; //to be changed later(calculate right after parsing)
	int b;
	int	colour;
	float dist_mult;

	dist_mult = 1.0f - (ray->results.hit_dist / max_dist);
	b = (int)(dist_mult * 0xff);
	colour = (b << 3 * 8) + (b << 2 * 8) + (b << 1 * 8) + 0xff;
	mlx_put_pixel(scene->g_img, x, y, colour);
}