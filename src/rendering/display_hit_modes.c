/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_hit_modes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:30:44 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/20 16:01:51 by mvan-rij         ###   ########.fr       */
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

unsigned char srgb_ftochar(float f)
{
	int ret;

	if (f < 0.003)
		return 0;
	ret = ((1.055 * powf(f,(1/2.4)) - 0.055)) * 255;
	//if ( ret > 255)
	//	return ((char)255);
	return (ret);
}


void	display_default(t_ray *ray, int x, int y, t_scene *scene)
{
	float	r;
	float	b;
	float	g;
	int	colour;
	float brightness;

	brightness = (ray->results.light_intensity + scene->ambient->ratio);
	if (brightness > 1.0f)
		brightness = 1.0f;
	r = (ray->results.obj_color.r / 0xff) * brightness;
	g = (ray->results.obj_color.g / 0xff) * brightness;
	b = (ray->results.obj_color.b / 0xff) * brightness;

	colour = (srgb_ftochar(r) << 3 * 8) + \
(srgb_ftochar(g) << 2 * 8) + \
(srgb_ftochar(b) << 1 * 8) + 0xff;
	mlx_put_pixel(scene->g_img, x, y, colour);
}

void	display_light_intensity(t_ray *ray, int x, int y, t_scene *scene)
{
	int b;
	int	colour;
	float brightness;

	brightness = (ray->results.light_intensity + scene->ambient->ratio);
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