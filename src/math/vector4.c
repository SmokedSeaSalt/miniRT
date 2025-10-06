/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egrisel <egrisel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 10:03:19 by egrisel           #+#    #+#             */
/*   Updated: 2025/10/06 12:50:46 by egrisel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"

t_vec4	vec4_new(float x, float y, float z, float w)
{
	t_vec4	result;

	result.x = x;
	result.y = y;
	result.z = z;
	result.w = w;
	return (result);
}

// Returns x + y + z + w
float	vec4_sum_components(t_vec4 vec4)
{
	return (vec4.x + vec4.y + vec4.z + vec4.w);
}
