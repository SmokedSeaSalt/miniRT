/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_hit_modes.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:30:44 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/30 12:37:17 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "structs.h"
#include "MLX42.h"

/// @brief displays the surface normal of the object.
/// @param ray
/// @param x
/// @param y
/// @param scene
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

/// @brief displays the normal vector in x = r, y = g, z = b representation.
/// @param ray
/// @param x
/// @param y
/// @param scene
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

/// @brief the standart ray tracer output. displays light and color values.
/// @param ray
/// @param x
/// @param y
/// @param scene
void	display_default(t_ray *ray, int x, int y, t_scene *scene)
{
	float	r;
	float	b;
	float	g;
	int		colour;

	r = (ray->results.light_intensity.r + scene->ambient->intensity.r);
	r = r * (ray->results.obj_color.r / 255);
	r += ray->results.specular_intensity.r;
	if (r > 1.0f)
		r = 1.0f;
	r *= 255;
	g = (ray->results.light_intensity.g + scene->ambient->intensity.g);
	g = g * (ray->results.obj_color.g / 255);
	g += ray->results.specular_intensity.g;
	if (g > 1.0f)
		g = 1.0f;
	g *= 255;
	b = (ray->results.light_intensity.b + scene->ambient->intensity.b);
	b = b * (ray->results.obj_color.b / 255);
	b += ray->results.specular_intensity.b;
	if (b > 1.0f)
		b = 1.0f;
	b *= 255;

	colour = ((int)r << 3 * 8) + ((int)g << 2 * 8) + ((int)b << 1 * 8) + 0xff;
	mlx_put_pixel(scene->g_img, x, y, colour);
}

/// @brief grayscale representation of average light intensity.
/// @param ray
/// @param x
/// @param y
/// @param scene
void	display_light_intensity(t_ray *ray, int x, int y, t_scene *scene)
{
	int		b;
	int		colour;
	float	brightness;

	brightness = ((ray->results.light_intensity.x + \
ray->results.light_intensity.y + ray->results.light_intensity.z) * 0.3333f);
	brightness += scene->ambient->ratio;
	if (brightness > 1.0f)
		brightness = 1.0f;
	b = (int)(brightness * 0xff);
	colour = (b << 3 * 8) + (b << 2 * 8) + (b << 1 * 8) + 0xff;
	mlx_put_pixel(scene->g_img, x, y, colour);
}

/// @brief grayscale representation of object distance from camera.
/// @param ray
/// @param x
/// @param y
/// @param scene
void	display_distance(t_ray *ray, int x, int y, t_scene *scene)
{
	int			b;
	int			colour;
	float		dist_mult;
	//to be changed later(calculate right after parsing)
	const float	max_dist = 2;

	dist_mult = 1.0f - (ray->results.hit_dist / max_dist);
	b = (int)(dist_mult * 0xff);
	colour = (b << 3 * 8) + (b << 2 * 8) + (b << 1 * 8) + 0xff;
	mlx_put_pixel(scene->g_img, x, y, colour);
}
