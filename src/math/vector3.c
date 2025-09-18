/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvan-rij <mvan-rij@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/18 16:16:16 by mvan-rij          #+#    #+#             */
/*   Updated: 2025/09/18 16:16:39 by mvan-rij         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "math_inc.h"
#include <math.h>

static inline t_vec3	vec3_new(float x, float y, float z)
{
	t_vec3	result;

	result.x = x;
	result.y = y;
	result.z = z;
	result.w = 0.0f;
	return (result);
}

t_vec3	normalize_vec3(t_vec3 vec3)
{
	float		length;
	t_vec3		result;

	length = sqrtf(vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z);
	if (length != 0.0f)
		result.v = vec3.v / vec3_new(length, length, length).v;
	else
		result = vec3_new(0, 0, 0);
	return (result);
}
