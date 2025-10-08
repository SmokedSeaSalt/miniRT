/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_miss_modes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 10:42:17 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/10/08 14:28:33 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42.h"
#include "structs.h"

void	display_black(t_ray *ray, int x, int y, t_scene *scene)
{
	(void)ray;
	mlx_put_pixel(scene->g_img, x, y, 0x000000ff);
}

void	display_white(t_ray *ray, int x, int y, t_scene *scene)
{
	(void)ray;
	mlx_put_pixel(scene->g_img, x, y, 0xffffffff);
}
