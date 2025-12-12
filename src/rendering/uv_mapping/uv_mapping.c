/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_mapping.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/11 12:47:08 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/12/12 16:43:52 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "consts.h"
#include "structs.h"
#include "MLX42.h"

static int	get_pixels_index(t_uv uv, mlx_texture_t *uv_map)
{
	const int	col_num = uv.u * (uv_map->width - 1);
	const int	row_num = uv.v * (uv_map->height - 1);
	return (4 * (row_num * uv_map->width + col_num));
}

t_color	get_uv_value_png(t_uv uv, mlx_texture_t *uv_map)
{
	int		pixels_index;
	t_color	color;
	(void)uv_map;

	uv.v = 1 - uv.v;
	
	pixels_index = get_pixels_index(uv, uv_map);
	color.r = uv_map->pixels[pixels_index++];
	color.g = uv_map->pixels[pixels_index++];
	color.b = uv_map->pixels[pixels_index];
	// color.r = uv.v * 255;
	// color.g = uv.u * 255;
	// color.b = 0;

	return (color);
}

//if in "black square return color" else return white
t_color	uv_checkerboard(t_uv uv, t_color color)
{
	const int	u2 = uv.u * CHECKER_U_NUM;
	const int	v2 = uv.v * CHECKER_V_NUM;

	if ((u2 + v2) % 2 == 0)
		return (color);
	else
		return ((t_color){.r = 255, .g = 255, .b = 255});
}
