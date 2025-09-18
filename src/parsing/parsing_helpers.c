/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_helpers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:45:52 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/18 17:18:45 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

int	count_arguments(char **line)
{
	int	i;

	i = 0;
	while (line[i] != NULL)
		i++;
	return (i);
}

int color_out_of_range(t_color color)
{
	if (color.r < 0 || color.r > 255 \
|| color.g < 0 || color.g > 255 \
|| color.b < 0 || color.b > 255)
		return (1);
	return (0);
}

int orientation_out_of_range(t_vec3 orientation)
{
	if (orientation.x < -1.0f || orientation.x > 1.0f \
|| orientation.y < -1.0f || orientation.y > 1.0f \
|| orientation.z < -1.0f || orientation.z > 1.0f)
		return (1);
	return (0);
}
