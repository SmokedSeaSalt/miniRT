/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_miss_modes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:42:17 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/22 14:57:14 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "structs.h"

/// @brief displays pixel as black.
/// @param ray
/// @param x
/// @param y
/// @param scene
void	display_black(t_ray *ray, int x, int y, t_scene *scene)
{
	(void)ray;
	mlx_put_pixel(scene->g_img, x, y, 0x000000ff);
}

/// @brief displays pixel as white.
/// @param ray
/// @param x
/// @param y
/// @param scene
void	display_white(t_ray *ray, int x, int y, t_scene *scene)
{
	(void)ray;
	mlx_put_pixel(scene->g_img, x, y, 0xffffffff);
}

/// @brief display gray plane with blue sky
/// @param ray
/// @param x
/// @param y
/// @param scene
void display_horizon_blue_sky(t_ray *ray, int x, int y, t_scene *scene)
{
	if (ray->vec3.z > 0.0f)
		mlx_put_pixel(scene->g_img, x, y, 0x47bbf5);
	else
		mlx_put_pixel(scene->g_img, x, y, 0x363636);
}