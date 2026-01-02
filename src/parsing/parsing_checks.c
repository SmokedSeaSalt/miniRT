/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_checks.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 14:58:50 by mvan-rij          #+#    #+#             */
/*   Updated: 2026/01/02 14:07:45 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

int	color_out_of_range(t_color color)
{
	if (color.r < 0 || color.r > 255 \
|| color.g < 0 || color.g > 255 \
|| color.b < 0 || color.b > 255)
		return (1);
	return (0);
}

int	orientation_out_of_range(t_vec3 orientation)
{
	if (orientation.x < -1.0f || orientation.x > 1.0f \
|| orientation.y < -1.0f || orientation.y > 1.0f \
|| orientation.z < -1.0f || orientation.z > 1.0f)
		return (1);
	return (0);
}

int	orientation_all_zero(t_vec3 orientation)
{
	if (orientation.x == 0.0f && orientation.y == 0.0f && orientation.z == 0.0f)
		return (1);
	return (0);
}
